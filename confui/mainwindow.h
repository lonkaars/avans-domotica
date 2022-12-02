#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include <QDebug>

#include "mesh_connector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CDMainWindow; }
QT_END_NAMESPACE

class CDMainWindow : public QMainWindow {
	Q_OBJECT

public:
	CDMeshConnector *mesh_connector = nullptr;
	
	CDMainWindow(QWidget *parent = nullptr);
	~CDMainWindow();
};
