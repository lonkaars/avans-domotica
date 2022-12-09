#pragma once

#include <QMainWindow>

#include "mainwindow.h"
#include "ui_node.h"
#include "ui_scroll_container.h"

class CDNodeOverviewTabWidget : public QWidget {
	Q_OBJECT

private:
	CDScrollContainerLayout* main_layout;
	map<cd_uid_t, CDNodeWidget*> node_widgets;

public:
	CDMainWindow *mainwindow = nullptr;
	
	CDNodeOverviewTabWidget(CDMainWindow *main_window = nullptr);
	virtual ~CDNodeOverviewTabWidget();
	virtual void update();
};
