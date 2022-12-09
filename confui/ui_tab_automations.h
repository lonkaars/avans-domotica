#pragma once

#include <QMainWindow>

#include "mainwindow.h"
#include "ui_automation.h"
#include "ui_scroll_container.h"

class CDAddAutomationWidget;
class CDAutomationsTabWidget : public QWidget {
	Q_OBJECT

private:
	CDScrollContainerLayout* main_layout;
	QVBoxLayout* automations;
	CDAddAutomationWidget* new_automation_button;
	map<cd_link_t, CDAutomationWidget*> automation_widgets;

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDAutomationsTabWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDAutomationsTabWidget();
	virtual void update();
};
