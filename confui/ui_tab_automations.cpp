#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "ui_tab_automations.h"
#include "ui_automation.h"

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

	update();
	setLayout(main_layout);
}

void CDAutomationsTabWidget::update() {
	map<cd_link_t, cd_s_automation*> links = this->mainwindow->mesh_connector->get_links();
	map<cd_link_t, CDAutomationWidget*> widgets;

	for (pair<cd_link_t, cd_s_automation*> link : links) {
		if (widgets.count(link.first)) { // node is already in list
			widgets[link.first]->update();
		} else {
			widgets[link.first] = new CDAutomationWidget(link.second, this);
		}
		main_layout->addWidget(widgets[link.first]);
	}
}

