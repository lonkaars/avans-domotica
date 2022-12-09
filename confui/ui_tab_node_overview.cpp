#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>

#include "ui_tab_node_overview.h"

using std::pair;

CDNodeOverviewTabWidget::~CDNodeOverviewTabWidget() {  }
CDNodeOverviewTabWidget::CDNodeOverviewTabWidget(CDMainWindow* main_window) : QWidget(main_window) {
	this->mainwindow = main_window;
	main_layout = new CDScrollContainerLayout(this);

	update();
	setLayout(main_layout);
}

void CDNodeOverviewTabWidget::update() {
	map<cd_uid_t, cd_s_node*> nodes = g_cd_mesh_connector->get_nodes(false);

	for (pair<cd_uid_t, cd_s_node*> node : nodes) {
		if (node_widgets.count(node.first)) { // node is already in list
			node_widgets[node.first]->update();
		} else {
			node_widgets[node.first] = new CDNodeWidget(this);
			node_widgets[node.first]->set_node(node.second);
			node_widgets[node.first]->update();
		}
		main_layout->addWidget(node_widgets[node.first]);
	}
}
