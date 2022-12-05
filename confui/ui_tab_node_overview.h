#pragma once

#include <QMainWindow>

#include "ui_scroll_container.h"
#include "mainwindow.h"

class CDNodeOverviewTabWidget : public QWidget {
	Q_OBJECT

private:
	CDScrollContainerLayout* main_layout;

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDNodeOverviewTabWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDNodeOverviewTabWidget();
	virtual void update();
};
