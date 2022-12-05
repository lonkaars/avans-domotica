#include "ui_automation.h"

CDAutomationWidget::~CDAutomationWidget() { }
CDAutomationWidget::CDAutomationWidget(cd_s_automation* automation, QWidget *parent) : QWidget(parent) {
	set_automation(automation);

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

	update();
	setLayout(main_layout);
}

void CDAutomationWidget::set_automation(cd_s_automation* automation) {
	_automation = automation;
}

void CDAutomationWidget::update() {
	button_remove->setText("Delete");

	dropdown_action->clear();
	dropdown_action->addItem("Toggles", CD_AUTOMATION_TYPE_TOGGLE);
	dropdown_action->addItem("Switches on", CD_AUTOMATION_TYPE_TURN_ON);
	dropdown_action->addItem("Switches off", CD_AUTOMATION_TYPE_TURN_OFF);
}
