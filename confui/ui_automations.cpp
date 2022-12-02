#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

#include "ui_automations.h"

CDAutomationsWidget::~CDAutomationsWidget() { }
CDAutomationsWidget::CDAutomationsWidget(CDMainWindow* main_window) : QWidget(main_window) {
	this->mainwindow = main_window;

	QVBoxLayout* main_layout = new QVBoxLayout;

	QLabel* label_test = new QLabel("Automations widget test");
	main_layout->addWidget(label_test);

	setLayout(main_layout);
}

