#pragma once

#include <QMainWindow>

#include "ui_scroll_container.h"
#include "mainwindow.h"

class CDAddAutomationWidget;
class CDAutomationsTabWidget : public QWidget {
	Q_OBJECT

private:
	CDScrollContainerLayout* main_layout;
	QVBoxLayout* automations;
	CDAddAutomationWidget* new_automation_button;

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDAutomationsTabWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDAutomationsTabWidget();
	virtual void update();
};
