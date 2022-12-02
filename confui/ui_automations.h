#pragma once

#include <QMainWindow>

#include "mainwindow.h"

class CDAutomationsWidget : public QWidget {
	Q_OBJECT

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDAutomationsWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDAutomationsWidget();
};
