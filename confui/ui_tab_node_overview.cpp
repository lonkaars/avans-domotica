#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "ui_tab_node_overview.h"
#include "ui_node.h"
#include "ui_automation.h"

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

CDNodeOverviewTabWidget::~CDNodeOverviewTabWidget() {  }
CDNodeOverviewTabWidget::CDNodeOverviewTabWidget(CDMainWindow* main_window) : QWidget(main_window) {
	this->mainwindow = main_window;

	QVBoxLayout* main_layout = new QVBoxLayout;

	const char* n_name = "berta";
	cd_s_node n = {
		.address = { 0x00, 0xff, 0x21, 0x69, 0xf2, 0x31 },
		.name_len = strlen(n_name),
		.name = n_name,
		.light_on = true,
		.provisioned = true,
	};

	cd_s_automation a = {
		.type = CD_AUTOMATION_TYPE_TOGGLE,
		.button = &n,
		.light = &n,
	};

	CDNodeWidget* nd_w = new CDNodeWidget(&n, this);
	CDAutomationWidget* au_w = new CDAutomationWidget(&a, this);
	CDAddAutomationWidget* ad_w = new CDAddAutomationWidget(this);

	main_layout->addWidget(nd_w);
	main_layout->addWidget(au_w);
	main_layout->addWidget(ad_w);

	setLayout(main_layout);
}
