#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "ui_tab_automations.h"

using std::pair;

class CDAddAutomationWidget : public QWidget {
public:
	CDAddAutomationWidget(QWidget* parent) : QWidget(parent) {
		QHBoxLayout* main_layout = new QHBoxLayout;
		QPushButton* button_add = new QPushButton("Add automation");

		main_layout->addStretch();
		main_layout->addWidget(button_add);
		main_layout->addStretch();

		setLayout(main_layout);
	}

	~CDAddAutomationWidget() {}
};


CDAutomationsTabWidget::~CDAutomationsTabWidget() { }
CDAutomationsTabWidget::CDAutomationsTabWidget(CDMainWindow* main_window) : QWidget(main_window) {
	this->mainwindow = main_window;
	main_layout = new CDScrollContainerLayout(this);
	automations = new QVBoxLayout;
	new_automation_button = new CDAddAutomationWidget(this);

	QWidget* automations_widget = new QWidget(this);
	automations_widget->setLayout(automations);

	main_layout->addWidget(automations_widget);
	main_layout->addWidget(new_automation_button);

	update();
	setLayout(main_layout);
}

void CDAutomationsTabWidget::update() {
	map<cd_link_t, cd_s_automation*> links = this->mainwindow->mesh_connector->get_links();

	for (pair<cd_link_t, cd_s_automation*> link : links) {
		if (automation_widgets.count(link.first) == 0) {
			automation_widgets[link.first] = new CDAutomationWidget(this); // create new automation
			automation_widgets[link.first]->set_automation(link.first, link.second);
			automation_widgets[link.first]->update();
			automations->addWidget(automation_widgets[link.first]);
		} else if (link.second != nullptr) {
			automation_widgets[link.first]->update(); // update existing widget
		} else if (automation_widgets[link.first] != nullptr) {
			automations->removeWidget(automation_widgets[link.first]); // remove removed automation
			delete automation_widgets[link.first]; // free automation widget
			automation_widgets[link.first] = nullptr;
		}
	}
}

