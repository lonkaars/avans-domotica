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

	update();
	setLayout(main_layout);
}

void CDNodeOverviewTabWidget::update() {
	vector<cd_s_node*> nodes = this->mainwindow->mesh_connector->get_nodes();
	map<uint8_t(*)[6], CDNodeWidget*> node_widgets;

	for (cd_s_node* node : nodes) {
		// c++ cast from uint8_t[6] to uint8_t* with length 6
		uint8_t (*addr)[6] = (uint8_t (*)[6]) node->address;
		if (node_widgets.count(addr)) { // node is already in list
			node_widgets[addr]->update();
		} else {
			node_widgets[addr] = new CDNodeWidget(node, this);
		}
		main_layout->addWidget(node_widgets[addr]);
	}
}
