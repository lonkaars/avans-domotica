#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "ui_tab_automations.h"

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

	QVBoxLayout* main_layout = new QVBoxLayout;

	QLabel* label_test = new QLabel("Automations widget test");
	main_layout->addWidget(label_test);

	setLayout(main_layout);
}

