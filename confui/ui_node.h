#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QString>

#include "mesh_connector.h"

class CDNodeWidget : public QWidget {
	Q_OBJECT

private:
	cd_s_node* _node;

	QHBoxLayout* main_layout;
	QLabel* label_node_name;
	QLabel* label_node_address;
	QCheckBox* switch_on_off;
	QPushButton* button_add_remove;

public:
	CDNodeWidget(cd_s_node* node, QWidget *parent = nullptr);
	virtual ~CDNodeWidget();
	virtual void update();
	virtual void set_node(cd_s_node* node);
	virtual void toggle_provision();
	virtual void update_led(bool on);
};
