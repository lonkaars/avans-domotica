#include "mainwindow.h"

CDMainWindow::CDMainWindow(QWidget *parent) : QMainWindow(parent) {
	this->mesh_connector = new CDMeshConnector();
}

CDMainWindow::~CDMainWindow() {
	delete this->mesh_connector;
}

