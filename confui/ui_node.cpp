#include "ui_node.h"

CDNodeWidget::~CDNodeWidget() { }
CDNodeWidget::CDNodeWidget(cd_s_node* node, QWidget *parent) : QWidget(parent) {
	set_node(node);

	main_layout = new QHBoxLayout;
	switch_on_off = new QCheckBox;
	button_add_remove = new QPushButton;
	label_node_address = new QLabel;
	label_node_name = new QLabel;

	main_layout->addWidget(label_node_name);
	main_layout->addWidget(label_node_address);
	main_layout->addStretch();
	main_layout->addWidget(switch_on_off);
	main_layout->addWidget(button_add_remove);

	connect(button_add_remove, &QPushButton::clicked, this, &CDNodeWidget::toggle_provision);
	connect(switch_on_off, &QCheckBox::toggled, this, &CDNodeWidget::update_led);

	update();
	setLayout(main_layout);
}

void CDNodeWidget::set_node(cd_s_node* node) {
	_node = node;
}

void CDNodeWidget::update() {
	QString	node_name = QString::fromLocal8Bit(_node->name, _node->name_len);
	label_node_name->setText(node_name);

	QString node_address = QString::fromStdString(cd_mac_to_string(_node->address));
	node_address.prepend("(");
	node_address.append(")");
	label_node_address->setText(node_address);

	switch_on_off->setText("on");
	switch_on_off->setVisible(_node->provisioned);
	switch_on_off->setCheckable(_node->provisioned);
	switch_on_off->setChecked(_node->light_on);

	button_add_remove->setText(_node->provisioned ? "Remove from network" : "Join network");
}

void CDNodeWidget::toggle_provision() {
	if (_node->provisioned) g_cd_mesh_connector->node_remove_network(_node);
	else g_cd_mesh_connector->node_join_network(_node);

	update();
}

void CDNodeWidget::update_led(bool on) {
	_node->light_on = on;
	g_cd_mesh_connector->update_node(_node);

	update();
}

