#include "serial.h"
#include "../shared/serial_parse.h"
#include "../shared/bin.h"
#include "../shared/pclient.h"
#include "mainwindow.h"
#include "mesh_connector.h"

#include <iostream>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

CDSerialConnector::CDSerialConnector() {
	this->_serial = new QSerialPort;

	if (!_serial->setBaudRate(QSerialPort::Baud115200)) qDebug() << _serial->errorString();
	if (!_serial->setDataBits(QSerialPort::Data8)) // data is 8 bits
		qDebug() << _serial->errorString();
	if (!_serial->setParity(QSerialPort::NoParity)) qDebug() << _serial->errorString();
	if (!_serial->setFlowControl(QSerialPort::NoFlowControl)) // default: QSerialPort::NoFlowControl
		qDebug() << _serial->errorString();
	if (!_serial->setStopBits(QSerialPort::OneStop)) // default
		qDebug() << _serial->errorString();
}

CDSerialConnector::~CDSerialConnector() { delete this->_serial; }

void CDSerialConnector::action() {
	int bytes = _serial->bytesAvailable();
	if (bytes > 0) _msg = _serial->readAll();

	string std_string = _msg.toStdString();
	size_t size = std_string.size();
	const char* data = std_string.c_str();
	for (size_t i = 0; i < size; i++)
		cd_serial_parse(data[i]);
}

void CDSerialConnector::write(QByteArray msg) {
	if (-1 == _serial->write(msg))
		qDebug() << _serial->errorString();
}

void CDSerialConnector::connect(string port) {
	_serial->setPortName(QString::fromStdString(port));

	if (!_serial->open(QIODevice::ReadWrite))
		qDebug() << _serial->errorString();

	QObject::connect(_serial, &QSerialPort::readyRead, [&] { action(); });
}

void CDSerialConnector::disconnect() {
	if (_serial->isOpen() == false) return;
	_serial->disconnect();
}

QByteArray CDSerialConnector::get_data() { return _msg; }

vector<string> CDSerialConnector::get_ports() {
	vector<string> ports;
	for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
		ports.push_back(port.portName().toStdString());
	return ports;
}

string CDSerialConnector::get_port() {
	return _serial->portName().toStdString();
}

extern "C" {

void cd_pclient_send(cd_s_bin* data) {
	QByteArray converted;
	converted.append("\xff", 1);
	for (size_t i = 0; i < data->bytes; i++) {
		size_t byte = data->data[i];
		byte == 0xff ? converted.append("\xff\xff", 2)
			: converted.append((char *) &byte, 1);
	}
	g_cd_serial->write(converted);
}

// receive handlers (node only)
void cd_cmd_get_node(cd_s_bin* data) { (void) data; }
void cd_cmd_post_led(cd_s_bin* data) { (void) data; }
void cd_cmd_post_link(cd_s_bin* data) { (void) data; }
void cd_cmd_post_net(cd_s_bin* data) { (void) data; }

void cd_cmd_ping(cd_s_bin* data) {
	CD_CAST_BIN(cd_s_cmd_ping, data, cast);

	cd_bin_repl_ntoh16(&cast->id); // fix endianness

	std::cout << "ping request with id " << cast->id << " received!" << std::endl;
	
	cd_s_bin* response = cd_cmd_res_status((cd_e_scmds) cast->opcode, cast->id, false);
	cd_pclient_send(response);
	free(response);
}

void cd_cmd_response_get_node_parse_node(cd_s_cmd_node* node) {
	printf("yes i am node with name '%.*s'\n", node->name_len, node->remaining_data);
	printf("my light is %s and i am%s provisioned\n", node->light_on ? "on" : "off", node->provisioned ? "" : " not");

	// get node handle
	cd_uid_t node_id = g_cd_mesh_connector->get_or_create_node_by_uuid(node->uuid);
	cd_s_node* gui_node = g_cd_mesh_connector->get_node(node_id);

	// fill current node
	memcpy(gui_node->address, node->address, sizeof(cd_mac_addr_t));
	memcpy(gui_node->uuid, node->uuid, sizeof(cd_uuid_t));
	gui_node->name_len = node->name_len;
	if (gui_node->name != nullptr) free(gui_node->name);
	char* name = (char*) malloc(node->name_len);
	memcpy(name, node->remaining_data, node->name_len);
	gui_node->name = name;
	gui_node->light_on = !!node->light_on;
	gui_node->provisioned = !!node->provisioned;

	cd_uuid_t* light_publish_addresses = (cd_uuid_t*) (&node->remaining_data[0] + node->name_len);
	for (unsigned i = 0; i < node->link_count; i++) {
		// find or create light node
		cd_uid_t light_id = g_cd_mesh_connector->get_or_create_node_by_uuid(light_publish_addresses[i]);
		cd_s_node* gui_light = g_cd_mesh_connector->get_node(light_id);
		memcpy(gui_light->uuid, light_publish_addresses[i], sizeof(cd_uuid_t)); // fill at least uuid (if node is not yet known)

		// find or create automation handle
		cd_link_t link_id = g_cd_mesh_connector->get_or_create_link_by_uuid(gui_light->uuid, light_publish_addresses[i]);
		cd_s_automation* gui_link = g_cd_mesh_connector->get_link(link_id);

		// fill automation
		gui_link->button = gui_node;
		gui_link->light = gui_light;
		gui_link->type = CD_AUTOMATION_TYPE_TOGGLE; //TODO: read from incoming data in future
		gui_link->valid = true;
	}

	g_cd_main_window->update();
}

void cd_cmd_response_get_node(cd_s_bin* data) {
	CD_CAST_BIN(cd_s_cmd_response, data, response_cast);
	cd_s_cmd_response_get_node* nodes = (cd_s_cmd_response_get_node*) &response_cast->response_info[0]; // yes
	cd_bin_repl_ntoh16(&nodes->node_count);
	cd_bin_repl_ntoh16(&nodes->remaining_size);

	std::cout << "get nodes response with id " << response_cast->response_id << " received!" << std::endl;
	printf("counting %d node%s\n", nodes->node_count, nodes->node_count == 1 ? "" : "s");

	cd_s_cmd_node* cursor = &nodes->nodes[0];
	for (unsigned int i = 0; i < nodes->node_count; i++) {
		cd_bin_repl_ntoh16(&cursor->remaining_size);
		cd_bin_repl_ntoh16(&cursor->link_count);
		cd_bin_repl_ntoh32(&cursor->button_pub);

		cd_cmd_response_get_node_parse_node(cursor);
		cursor += sizeof(cd_s_cmd_node) + cd_bin_ntoh16(cursor->remaining_size);
	}
}

void cd_cmd_response_ping(cd_s_bin* data) {
	CD_CAST_BIN(cd_s_cmd_response, data, cast);
	std::cout << "ping response with id " << cast->response_id << " received!" << std::endl;
}

void cd_cmd_response(cd_s_bin* data) {
	CD_CAST_BIN(cd_s_cmd_response, data, cast);
	
	cd_bin_repl_ntoh16(&cast->id);
	cd_bin_repl_ntoh16(&cast->response_id);

	switch (cast->response_type) {
		case CD_CMD_PING: return cd_cmd_response_ping(data);
		case CD_CMD_GET_NODE: return cd_cmd_response_get_node(data);
		case CD_CMD_POST_LED: return; // TODO
		case CD_CMD_POST_LINK: return; // TODO
		case CD_CMD_POST_NET: return; // TODO
		default: return;
	}
}

}
