#pragma once

#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "mesh_connector.h"

class CDAutomationsTabWidget;
/** @brief widget that displays single automation */
class CDAutomationWidget : public QWidget {
	Q_OBJECT

private:
	cd_s_automation *_automation = nullptr;
	cd_link_t _id;
	CDAutomationsTabWidget *_parent = nullptr;

	QHBoxLayout *main_layout;
	QComboBox *dropdown_button;
	QComboBox *dropdown_action;
	QComboBox *dropdown_light;
	QPushButton *button_remove;

public:
	CDAutomationWidget(QWidget *parent = nullptr);
	virtual ~CDAutomationWidget();
	/** @brief redraw ui with new values */
	virtual void update();
	/** @brief register automation that this widget controls */
	virtual void set_automation(cd_link_t link);
	/** @brief test if all fields are valid / entered */
	virtual bool conf_valid();
	/** @brief apply new automation rule */
	virtual void apply();
	/** @brief remove automation */
	virtual void remove();
};
