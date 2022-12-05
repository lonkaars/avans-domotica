#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include <QDebug>

#include "mesh_connector.h"

class CDAutomationsTabWidget;
class CDNodeOverviewTabWidget;

class CDMainWindow : public QMainWindow {
	Q_OBJECT

public:
	CDMeshConnector *mesh_connector = nullptr;
	CDAutomationsTabWidget* automations_widget = nullptr;
	CDNodeOverviewTabWidget* node_overview_widget = nullptr;
	
	CDMainWindow(QWidget *parent = nullptr);
	~CDMainWindow();
};
