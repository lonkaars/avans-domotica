#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QString>

#include "ui_node.h"

CDNodeWidget::~CDNodeWidget() { }
CDNodeWidget::CDNodeWidget(cd_s_node* node, QWidget *parent) : QWidget(parent) {
	_node = node;
	QHBoxLayout* main_layout = new QHBoxLayout;
	QHBoxLayout* float_left = new QHBoxLayout;
	QHBoxLayout* float_right = new QHBoxLayout;

	QString	node_name = QString::fromLocal8Bit(_node->name, _node->name_len);
	QString node_address = QString::fromStdString(cd_node_mac_string(_node->address));
	node_address.prepend("(");
	node_address.append(")");
	QLabel* label_node_name = new QLabel(node_name, this);
	QLabel* label_node_address = new QLabel(node_address, this);
	float_left->addWidget(label_node_name);
	float_left->addWidget(label_node_address);

	float_left->addStretch();
	float_right->addStretch();

	QCheckBox* switch_on_off = new QCheckBox("on", this);
	switch_on_off->setCheckable(_node->provisioned);
	QPushButton* button_add_remove = new QPushButton(_node->provisioned ? "Remove from network" : "Join network", this);
	float_right->addWidget(switch_on_off);
	float_right->addWidget(button_add_remove);

	main_layout->addLayout(float_left);
	main_layout->addLayout(float_right);
	setLayout(main_layout);
}
