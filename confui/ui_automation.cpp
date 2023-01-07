#include "ui_automation.h"
#include "mesh_connector.h"
#include "ui_tab_automations.h"

using std::pair;

CDAutomationWidget::~CDAutomationWidget() {}
CDAutomationWidget::CDAutomationWidget(QWidget *parent) : QWidget(parent) {
	_parent		= (CDAutomationsTabWidget *)parent;
	main_layout = new QHBoxLayout;

	dropdown_button = new QComboBox;
	dropdown_action = new QComboBox;
	dropdown_light	= new QComboBox;
	button_remove	= new QPushButton("Delete");

	main_layout->addWidget(dropdown_button);
	main_layout->addWidget(dropdown_action);
	main_layout->addWidget(dropdown_light);
	main_layout->addStretch();
	main_layout->addWidget(button_remove);

	connect(button_remove, &QPushButton::clicked, this, &CDAutomationWidget::remove);

	connect(dropdown_button, qOverload<int>(&QComboBox::activated), this, &CDAutomationWidget::apply);
	connect(dropdown_action, qOverload<int>(&QComboBox::activated), this, &CDAutomationWidget::apply);
	connect(dropdown_light, qOverload<int>(&QComboBox::activated), this, &CDAutomationWidget::apply);

	update();
	setLayout(main_layout);
}

void CDAutomationWidget::set_automation(cd_link_t link) {
	_id			= link;
	_automation = g_cd_mesh_connector->get_link(link);
}

void CDAutomationWidget::update() {
	map<cd_uid_t, cd_s_node *> nodes = g_cd_mesh_connector->get_nodes(false);

	dropdown_button->clear();
	dropdown_light->clear();
	for (pair<cd_uid_t, cd_s_node *> node : nodes) {
		QString label = "";
		label.append(QString::fromLocal8Bit(node.second->name, node.second->name_len));
		label.append(" (");
		label.append(QString::fromStdString(CDMeshConnector::cd_mac_to_string(node.second->address)));
		label.append(")");

		dropdown_button->addItem(label, node.second->id);
		dropdown_light->addItem(label, node.second->id);
	}

	dropdown_action->clear();
	dropdown_action->addItem("Toggles", CD_AUTOMATION_TYPE_TOGGLE);
	dropdown_action->addItem("Switches on", CD_AUTOMATION_TYPE_TURN_ON);
	dropdown_action->addItem("Switches off", CD_AUTOMATION_TYPE_TURN_OFF);

	if (_automation == nullptr) return;

	dropdown_button->setCurrentIndex(_automation->button == nullptr ? -1 : dropdown_button->findData(_automation->button->id));
	dropdown_action->setCurrentIndex(dropdown_action->findData(_automation->type));
	dropdown_light->setCurrentIndex(_automation->light == nullptr ? -1 : dropdown_light->findData(_automation->light->id));
}

bool CDAutomationWidget::conf_valid() {
	if (dropdown_button->currentIndex() == -1) return false;
	if (dropdown_action->currentIndex() == -1) return false;
	if (dropdown_light->currentIndex() == -1) return false;
	return true;
}

void CDAutomationWidget::apply() {
	if (!conf_valid()) return;

	_automation->button = g_cd_mesh_connector->get_node(dropdown_button->findData(dropdown_button->currentIndex()));
	_automation->type	= (cd_e_automation_type)dropdown_action->findData(dropdown_action->currentIndex());
	_automation->light	= g_cd_mesh_connector->get_node(dropdown_light->findData(dropdown_light->currentIndex()));
	_automation->valid	= true;

	g_cd_mesh_connector->update_link(_automation, true);
}

void CDAutomationWidget::remove() {
	g_cd_mesh_connector->remove_link(_id);
	if (_parent != nullptr) _parent->update();
}
