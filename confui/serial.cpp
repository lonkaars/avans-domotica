#include "serial.h"

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

CDSerialConnector::CDSerialConnector() {
	this->_serial = new QSerialPort;

	_serial->setPortName("/Users/jregnier/ttypx");
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
	// this is called when readyRead();
	int bytes = _serial->bytesAvailable();
	if (bytes > 0) {
		qDebug() << "new Data arived" << _serial->bytesAvailable();
		_msg = _serial->readAll();
		qDebug() << _msg;
	}
}

void CDSerialConnector::write(QByteArray msg) {
	_serial->write(msg);
	qDebug() << _serial->errorString();
}

void CDSerialConnector::connect() {

	//    QIODevice::ReadOnly
	if (!_serial->open(QIODevice::ReadWrite)) qDebug() << _serial->errorString();

	QObject::connect(_serial, &QSerialPort::readyRead, [&] {
		// this is called when readyRead();
		action();
	});
}

void CDSerialConnector::disconnect() {
	// WIP?
}

QByteArray CDSerialConnector::get_data() { return _msg; }

vector<string> CDSerialConnector::get_ports() {
	vector<string> ports;
	for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
		ports.push_back(port.portName().toStdString());
	return ports;
}
