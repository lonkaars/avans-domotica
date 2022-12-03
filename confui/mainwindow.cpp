#include <QMenuBar>
#include <QGridLayout>
#include <QTabWidget>

#include "mainwindow.h"
#include "ui_automations.h"
#include "ui_node_overview.h"

CDMainWindow::CDMainWindow(QWidget *parent) : QMainWindow(parent) {
	this->mesh_connector = new CDMeshConnector();

	QMenuBar* menu_bar = new QMenuBar(this);
	menu_bar->addMenu("ayo");

	QTabWidget* tab_bar_widget = new QTabWidget(this);
	this->automations_widget = new CDAutomationsWidget(this);
	this->node_overview_widget = new CDNodeOverviewWidget(this);

	tab_bar_widget->addTab(this->node_overview_widget, "node overview");
	tab_bar_widget->addTab(this->automations_widget, "automations");

	setMenuBar(menu_bar);
	setCentralWidget(tab_bar_widget);
	setWindowTitle("confui");
}

CDMainWindow::~CDMainWindow() {
	delete this->mesh_connector;
}

