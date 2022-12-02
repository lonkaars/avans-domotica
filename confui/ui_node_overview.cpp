#include <QWidget>
#include <QLabel>

#include "ui_node_overview.h"

CDNodeOverviewWidget::~CDNodeOverviewWidget() {  }
CDNodeOverviewWidget::CDNodeOverviewWidget(CDMainWindow* main_window) : QWidget(main_window) {
	this->mainwindow = main_window;
}
