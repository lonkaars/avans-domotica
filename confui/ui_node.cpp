#include "ui_node.h"

CDNodeWidget::~CDNodeWidget() { }
CDNodeWidget::CDNodeWidget(cd_s_node* node, QWidget *parent) : QWidget(parent) {
	set_node(node);

	main_layout = new QHBoxLayout;
	float_left = new QHBoxLayout;
	float_right = new QHBoxLayout;
	switch_on_off = new QCheckBox;
	button_add_remove = new QPushButton;
	label_node_address = new QLabel;
	label_node_name = new QLabel;

	float_left->addWidget(label_node_name);
	float_left->addWidget(label_node_address);
	float_left->addStretch();

	float_right->addStretch();
	float_right->addWidget(switch_on_off);
	float_right->addWidget(button_add_remove);

	main_layout->addLayout(float_left);
	main_layout->addLayout(float_right);

	update();
	setLayout(main_layout);
}

void CDNodeWidget::set_node(cd_s_node* node) {
	_node = node;
}

void CDNodeWidget::update() {
	QString	node_name = QString::fromLocal8Bit(_node->name, _node->name_len);
	label_node_name->setText(node_name);

	QString node_address = QString::fromStdString(cd_node_mac_string(_node->address));
	node_address.prepend("(");
	node_address.append(")");
	label_node_address->setText(node_address);

	switch_on_off->setText("on");
	switch_on_off->setVisible(_node->provisioned);
	switch_on_off->setCheckable(_node->provisioned);
	switch_on_off->setChecked(_node->light_on);

	button_add_remove->setText(_node->provisioned ? "Remove from network" : "Join network");
}
