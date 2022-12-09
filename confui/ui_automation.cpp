#include "ui_automation.h"
#include "mesh_connector.h"

using std::pair;

CDAutomationWidget::~CDAutomationWidget() { }
CDAutomationWidget::CDAutomationWidget(QWidget* parent) : QWidget(parent) {
	main_layout = new QHBoxLayout;

	dropdown_button = new QComboBox;
	dropdown_action = new QComboBox;
	dropdown_light = new QComboBox;
	button_remove = new QPushButton;

	main_layout->addWidget(dropdown_button);
	main_layout->addWidget(dropdown_action);
	main_layout->addWidget(dropdown_light);
	main_layout->addStretch();
	main_layout->addWidget(button_remove);

	connect(button_remove, &QPushButton::clicked, this, &CDAutomationWidget::remove);

	update();
	setLayout(main_layout);
}

void CDAutomationWidget::set_automation(cd_link_t link, cd_s_automation* automation) {
	_id = link;
	_automation = automation;
}

void CDAutomationWidget::update() {
	button_remove->setText("Delete");

	map<cd_uid_t, cd_s_node*> nodes = g_cd_mesh_connector->get_nodes(false);

	dropdown_button->clear();
	dropdown_light->clear();
	for (pair<cd_uid_t, cd_s_node*> node : nodes) {
		QString label = "";
		label.append(QString::fromLocal8Bit(node.second->name, node.second->name_len));
		label.append(" (");
		label.append(QString::fromStdString(CDMeshConnector::cd_mac_to_string(node.second->address)));
		label.append(")");

		QString userData = QString::fromLocal8Bit((char*) node.second->address, 6);
		dropdown_button->addItem(label, userData);
		dropdown_light->addItem(label, userData);
	}

	if (_automation == nullptr) return;

	dropdown_button->setCurrentIndex(dropdown_button->findData(QString::fromLocal8Bit((char*) _automation->button->address, 6)));

	dropdown_action->clear();
	dropdown_action->addItem("Toggles", CD_AUTOMATION_TYPE_TOGGLE);
	dropdown_action->addItem("Switches on", CD_AUTOMATION_TYPE_TURN_ON);
	dropdown_action->addItem("Switches off", CD_AUTOMATION_TYPE_TURN_OFF);
	dropdown_action->setCurrentIndex(dropdown_action->findData(_automation->type));

	dropdown_light->setCurrentIndex(dropdown_light->findData(QString::fromLocal8Bit((char*) _automation->light->address, 6)));
}

bool CDAutomationWidget::conf_valid() {
	return true;
}

void CDAutomationWidget::apply() {
	if (!conf_valid()) return;

	g_cd_mesh_connector->update_link(_id, _automation);
}

void CDAutomationWidget::remove() {
	g_cd_mesh_connector->remove_link(_id);
}
