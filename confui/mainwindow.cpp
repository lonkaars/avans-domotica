#include <QGridLayout>
#include <QMenuBar>
#include <QTabWidget>
#include <iostream>

#include "../shared/pclient.h"
#include "main.h"
#include "mainwindow.h"
#include "serial.h"
#include "ui_tab_automations.h"
#include "ui_tab_node_overview.h"

CDMeshConnector *g_cd_mesh_connector = nullptr;
CDSerialConnector *g_cd_serial		 = nullptr;
QApplication *g_cd_app				 = nullptr;

CDMainWindow::~CDMainWindow() {
	delete g_cd_mesh_connector;
	delete g_cd_serial;
}

CDMainWindow::CDMainWindow(QWidget *parent) : QMainWindow(parent) {
	g_cd_mesh_connector	   = new CDMeshConnector();
	this->mesh_connector   = g_cd_mesh_connector;
	g_cd_serial			   = new CDSerialConnector();
	this->serial_connector = g_cd_serial;

	menu_bar = new QMenuBar(this);

	QTabWidget *tab_bar_widget = new QTabWidget(this);

	automations_tab	  = new CDAutomationsTabWidget(this);
	node_overview_tab = new CDNodeOverviewTabWidget(this);

	tab_bar_widget->addTab(this->node_overview_tab, "node overview");
	tab_bar_widget->addTab(this->automations_tab, "automations");

	// manually connect to serial port
	if (g_cd_app->arguments().length() > 1 && g_cd_app->arguments().at(1).length() > 0) g_cd_serial->connect(g_cd_app->arguments().at(1).toStdString());

	setMenuBar(menu_bar);
	setCentralWidget(tab_bar_widget);
	update();
}

void CDMainWindow::update() {
	// update tabs (children widgets)
	automations_tab->update();
	node_overview_tab->update();

	setWindowTitle("confui");

	menu_bar->clear();
	QMenu *menu_options = menu_bar->addMenu("options");

	QAction *menu_options_refresh = menu_options->addAction("refresh node list");
	connect(menu_options_refresh, &QAction::triggered, this, &CDMainWindow::menu_refresh);

	QAction *menu_options_add_automation = menu_options->addAction("add automation");
	connect(menu_options_add_automation, &QAction::triggered, this, &CDMainWindow::menu_add_automation);

	QString serial_port_menu_label = "serial port";
	string port_name			   = g_cd_serial->get_port();
	if (port_name.size() > 0) {
		serial_port_menu_label.append(" (");
		serial_port_menu_label.append(QString::fromStdString(port_name));
		serial_port_menu_label.append(")");
	}
	QMenu *menu_options_serialport = menu_options->addMenu(serial_port_menu_label);

	vector<string> ports = CDSerialConnector::get_ports();
	for (string port : ports) {
		QAction *menu_port = menu_options_serialport->addAction(QString::fromStdString(port));
		connect(menu_port, &QAction::triggered, this, [this, port]() { menu_set_serial_port(port); });
	}

	cd_s_bin *msg = cd_cmd_gen_get_node(true, NULL);
	cd_pclient_send(msg);
	free(msg);
}

void CDMainWindow::menu_refresh() { update(); }

void CDMainWindow::menu_add_automation() {
	g_cd_mesh_connector->create_link();
	update();
}

void CDMainWindow::menu_set_serial_port(string new_port) {
	g_cd_serial->disconnect();
	g_cd_serial->connect(new_port);
	update();
}
