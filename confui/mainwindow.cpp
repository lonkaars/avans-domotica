#include <QMenuBar>
#include <QGridLayout>
#include <QTabWidget>

#include "mainwindow.h"
#include "ui_tab_automations.h"
#include "ui_tab_node_overview.h"

CDMeshConnector* g_cd_mesh_connector = nullptr;

CDMainWindow::~CDMainWindow() {
	delete this->mesh_connector;
}

CDMainWindow::CDMainWindow(QWidget *parent) : QMainWindow(parent) {
	g_cd_mesh_connector = new CDMeshConnector();
	this->mesh_connector = g_cd_mesh_connector;

	menu_bar = new QMenuBar(this);

	QTabWidget* tab_bar_widget = new QTabWidget(this);

	automations_tab = new CDAutomationsTabWidget(this);
	node_overview_tab = new CDNodeOverviewTabWidget(this);

	tab_bar_widget->addTab(this->node_overview_tab, "node overview");
	tab_bar_widget->addTab(this->automations_tab, "automations");

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
	QMenu* menu_options = menu_bar->addMenu("options");

	QAction* menu_options_refresh = menu_options->addAction("refresh node list");
	connect(menu_options_refresh, &QAction::triggered, this, &CDMainWindow::menu_refresh);

	QAction* menu_options_add_automation = menu_options->addAction("add automation");
	connect(menu_options_add_automation, &QAction::triggered, this, &CDMainWindow::menu_add_automation);

	QMenu* menu_options_serialport = menu_options->addMenu("serial port (FIXME)");

	menu_options_serialport->addAction("FIXME A");
	menu_options_serialport->addAction("FIXME B");
}

void CDMainWindow::menu_refresh() {
	update();
}

void CDMainWindow::menu_add_automation() {
	g_cd_mesh_connector->create_link();
	update();
}

