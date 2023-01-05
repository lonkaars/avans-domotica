#include "serial.h"
#include "../shared/serial_parse.h"
#include "../shared/bin.h"
#include "../shared/pclient.h"

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
	
	// cd_s_bin* response = cd_cmd_res_status((cd_e_scmds) cast->opcode, cast->id, false);
	// cd_pclient_send(response);
	// free(response);
	// response = nullptr;

	cd_uuid_t light_addrs[] = {
		{ 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef, 0x00, 0x00, 0x00, 0x00 },
	};
	cd_s_cmd_node* test = cd_cmd_node_alloc("gert", {
		.uuid = { 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef, 0x00, 0x00, 0x00, 0x00 },
		.address = { 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, },
		.light_on = false,
		.provisioned = false,
		.button_pub = 0xdeadbeef,
	}, 1, light_addrs);
	cd_s_bin* testres = cd_cmd_res(CD_CMD_GET_NODE, 0xf88f, cd_cmd_node_sizeof(test), (uint8_t*) test);
	free(test);

	cd_pclient_send(testres);
	free(testres);
}

void cd_cmd_response(cd_s_bin* data) {
	CD_CAST_BIN(cd_s_cmd_response, data, cast);
	
	cd_bin_repl_ntoh16(&cast->id);
	cd_bin_repl_ntoh16(&cast->response_id);

	switch (cast->response_type) {
		case CD_CMD_PING: {
			std::cout << "ping response with id " << cast->response_id << " received!" << std::endl;
			break;
		}
		default: { }
	}
}

}
