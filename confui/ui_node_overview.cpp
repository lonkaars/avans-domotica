#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "ui_node_overview.h"
#include "ui_node.h"

CDNodeOverviewWidget::~CDNodeOverviewWidget() {  }
CDNodeOverviewWidget::CDNodeOverviewWidget(CDMainWindow* main_window) : QWidget(main_window) {
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

	CDNodeWidget* nd_w = new CDNodeWidget(&n, this);

	main_layout->addWidget(nd_w);

	setLayout(main_layout);
}
