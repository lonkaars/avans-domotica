#include "serial.h"
#include "../shared/serial_parse.h"
#include "../shared/bin.h"

#include <iostream>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

CDSerialConnector::CDSerialConnector() {
	this->_serial = new QSerialPort;

	if (!_serial->setBaudRate(QSerialPort::Baud9600)) qDebug() << _serial->errorString();
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
	_serial->write(msg);
	qDebug() << _serial->errorString();
}

void CDSerialConnector::connect(string port) {
	_serial->setPortName(QString::fromStdString(port));

	//    QIODevice::ReadOnly
	if (!_serial->open(QIODevice::ReadWrite)) qDebug() << _serial->errorString();

	QObject::connect(_serial, &QSerialPort::readyRead, [&] {
		// this is called when readyRead();
		action();
	});
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

// receive handlers (node only)
void cd_cmd_get_node(cd_s_bin* data) { (void) data; }
void cd_cmd_post_led(cd_s_bin* data) { (void) data; }
void cd_cmd_post_link(cd_s_bin* data) { (void) data; }
void cd_cmd_post_net(cd_s_bin* data) { (void) data; }

void cd_cmd_ping(cd_s_bin* data) {
	CD_CAST_BIN(cd_s_cmd_ping, data, cast);

	cd_bin_repl_ntoh16(&cast->id); // fix endianness

	std::cout << "ping with id " << cast->id << " received!" << std::endl;
	
	// TODO: send ping back
}

void cd_cmd_response(cd_s_bin* data) {
	(void) data;
	
	std::cout << "received!" << std::endl;

	return;
}

}
