#include "ui_node.h"
#include "../shared/pclient.h"

CDNodeWidget::~CDNodeWidget() {}
CDNodeWidget::CDNodeWidget(QWidget *parent) : QWidget(parent) {
	main_layout		   = new QHBoxLayout;
	switch_on_off	   = new QCheckBox;
	button_add_remove  = new QPushButton;
	label_node_address = new QLabel;
	label_node_name	   = new QLabel;

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

void CDNodeWidget::set_node(cd_uid_t id) {
	_id	  = id;
	_node = g_cd_mesh_connector->get_node(id);
}

void CDNodeWidget::update() {
	if (_node == nullptr) return;

	QString node_name = QString::fromLocal8Bit(_node->name, _node->name_len);
	label_node_name->setText(node_name);

	QString node_address = QString::fromStdString(CDMeshConnector::cd_mac_to_string(_node->address));
	node_address.prepend("(");
	node_address.append(")");
	label_node_address->setText(node_address);

	switch_on_off->setText("on");
	switch_on_off->setVisible(_node->provisioned);
	switch_on_off->setCheckable(_node->provisioned);
	switch_on_off->setChecked(_node->light_on);

	button_add_remove->setText(_node->provisioned ? "Remove from network" : "Join network");

	cd_s_bin* msg = cd_cmd_gen_get_node(false, this->_node->uuid);
	cd_pclient_send(msg);
	free(msg);
}

void CDNodeWidget::toggle_provision() {
	if (_node->provisioned) g_cd_mesh_connector->network_remove_node(_node);
	else g_cd_mesh_connector->network_join_node(_node);

	update();
}

void CDNodeWidget::update_led(bool on) {
	_node->light_on = on;
	g_cd_mesh_connector->update_node(_node, true);

	update();
}
