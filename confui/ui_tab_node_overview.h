#pragma once

#include <QMainWindow>

#include "mainwindow.h"

class CDNodeOverviewTabWidget : public QWidget {
	Q_OBJECT

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDNodeOverviewTabWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDNodeOverviewTabWidget();
	virtual void update();
};
