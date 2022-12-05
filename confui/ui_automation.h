#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QComboBox>

#include "mesh_connector.h"

class CDAutomationWidget : public QWidget {
	Q_OBJECT

private:
	cd_s_automation* _automation;

	QHBoxLayout* main_layout;
	QComboBox* dropdown_button;
	QComboBox* dropdown_action;
	QComboBox* dropdown_light;
	QPushButton* button_remove;

public:
	CDAutomationWidget(cd_s_automation* automation, QWidget *parent = nullptr);
	virtual ~CDAutomationWidget();
	virtual void update();
	virtual void set_automation(cd_s_automation* automation);
};
