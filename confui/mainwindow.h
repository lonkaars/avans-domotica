#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include <QDebug>

#include "mesh_connector.h"
#include "serial.h"

class CDAutomationsTabWidget;
class CDNodeOverviewTabWidget;

/**
 * @brief main window
 *
 * creates menu bar and tabs
 * cascading refresh (automatic and manual)
 */
class CDMainWindow : public QMainWindow {
	Q_OBJECT

private:
	QMenuBar *menu_bar						   = nullptr;
	CDAutomationsTabWidget *automations_tab	   = nullptr;
	CDNodeOverviewTabWidget *node_overview_tab = nullptr;

public:
	CDMeshConnector *mesh_connector = nullptr;
	CDSerialConnector *serial_connector = nullptr;

	CDMainWindow(QWidget *parent = nullptr);
	~CDMainWindow();
	/** @brief update user interface */
	virtual void update();
	/** @brief menu bar refresh action handler */
	virtual void menu_refresh();
	/** @brief menu bar add automation action handler */
	virtual void menu_add_automation();
	/** @brief menu bar set serial port action handler */
	void menu_set_serial_port(string new_port);
};
