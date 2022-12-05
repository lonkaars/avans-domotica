#pragma once

#include <QMainWindow>

#include "ui_scroll_container.h"
#include "mainwindow.h"

class CDAutomationsTabWidget : public QWidget {
	Q_OBJECT

private:
	CDScrollContainerLayout* main_layout;

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDAutomationsTabWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDAutomationsTabWidget();
	virtual void update();
};
