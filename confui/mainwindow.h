#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include <QDebug>

#include "mesh_connector.h"

class CDAutomationsTabWidget;
class CDNodeOverviewTabWidget;

class CDMainWindow : public QMainWindow {
	Q_OBJECT
private:
	QMenuBar* menu_bar = nullptr;
	CDAutomationsTabWidget* automations_tab = nullptr;
	CDNodeOverviewTabWidget* node_overview_tab = nullptr;

public:
	CDMeshConnector *mesh_connector = nullptr;
	
	CDMainWindow(QWidget *parent = nullptr);
	~CDMainWindow();
	virtual void update();
	virtual void menu_refresh();
	virtual void menu_add_automation();
};
