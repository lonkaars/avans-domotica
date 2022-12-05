#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>

#include "ui_tab_node_overview.h"
#include "ui_node.h"

CDNodeOverviewTabWidget::~CDNodeOverviewTabWidget() {  }
CDNodeOverviewTabWidget::CDNodeOverviewTabWidget(CDMainWindow* main_window) : QWidget(main_window) {
	this->mainwindow = main_window;
	main_layout = new CDScrollContainerLayout(this);

	vector<cd_s_node*> nodes = this->mainwindow->mesh_connector->get_nodes();
	CDNodeWidget* nd_w = new CDNodeWidget(nodes[0], this);

	main_layout->addWidget(nd_w);

	update();
	setLayout(main_layout);
}

void CDNodeOverviewTabWidget::update() {

}
