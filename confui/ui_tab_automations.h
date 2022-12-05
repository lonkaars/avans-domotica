#pragma once

#include <QMainWindow>

#include "mainwindow.h"

class CDAutomationsTabWidget : public QWidget {
	Q_OBJECT

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDAutomationsTabWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDAutomationsTabWidget();
};
