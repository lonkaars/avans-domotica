#pragma once

#include <QMainWindow>

#include "mainwindow.h"

class CDNodeOverviewWidget : public QWidget {
	Q_OBJECT

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDNodeOverviewWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDNodeOverviewWidget();
};
