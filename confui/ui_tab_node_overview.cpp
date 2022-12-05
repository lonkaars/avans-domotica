#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>

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
	QScrollArea* scroll_area = new QScrollArea;
	QWidget* scroll_container = new QWidget;
	QVBoxLayout* scroll_inner = new QVBoxLayout;

	scroll_area->setWidgetResizable(true);
	scroll_area->setFrameShape(QFrame::NoFrame);
	scroll_area->setBackgroundRole(QPalette::Window);
	scroll_area->setFrameShadow(QFrame::Plain);
	scroll_area->setWidget(scroll_container);
	scroll_area->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	scroll_container->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	scroll_container->setLayout(scroll_inner);

	vector<cd_s_node*> nodes = this->mainwindow->mesh_connector->get_nodes();
	CDNodeWidget* nd_w = new CDNodeWidget(nodes[0], this);

	scroll_inner->addWidget(nd_w);

	main_layout->addWidget(scroll_area);

	update();
	setLayout(main_layout);
}

void CDNodeOverviewTabWidget::update() {

}
