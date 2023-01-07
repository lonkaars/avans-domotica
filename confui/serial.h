#pragma once

#include <QSerialPort>
#include <QString>
#include <vector>

using std::string;
using std::vector;

/** @brief manage asynchronous serial connection */
class CDSerialConnector {
public:
	CDSerialConnector();
	virtual ~CDSerialConnector();

	/** @brief get list of available serial ports */
	static vector<string> get_ports();

	/** @brief open serial port */
	virtual void connect(string port);
	/** @brief close serial port */
	virtual void disconnect();

	/** @brief write to serial port */
	virtual void write(QByteArray msg);
	/** @brief get last message */
	virtual QByteArray get_data();

	/** @brief get current port name */
	virtual string get_port();

private:
	/** @brief executed when new data is received */
	virtual void action();

	QSerialPort *_serial = nullptr;
	QByteArray _msg;
};

/** @brief global pointer to serial connector, initialized in CDMainWindow */
extern CDSerialConnector *g_cd_serial;

