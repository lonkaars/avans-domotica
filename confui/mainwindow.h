#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include <QDebug>

#include "mesh_connector.h"

class CDAutomationsWidget;
class CDNodeOverviewWidget;

class CDMainWindow : public QMainWindow {
	Q_OBJECT

public:
	CDMeshConnector *mesh_connector = nullptr;
	CDAutomationsWidget* automations_widget = nullptr;
	CDNodeOverviewWidget* node_overview_widget = nullptr;
	
	CDMainWindow(QWidget *parent = nullptr);
	~CDMainWindow();
};
