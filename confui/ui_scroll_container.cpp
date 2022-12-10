#include "ui_scroll_container.h"

CDScrollContainerLayout::~CDScrollContainerLayout() {}
CDScrollContainerLayout::CDScrollContainerLayout(QWidget *parent) : QVBoxLayout(parent) {
	scroll_area		 = new QScrollArea;
	scroll_container = new QWidget;
	scroll_inner	 = new QVBoxLayout;

	scroll_area->setWidgetResizable(true);
	scroll_area->setFrameShape(QFrame::NoFrame);
	scroll_area->setBackgroundRole(QPalette::Window);
	scroll_area->setFrameShadow(QFrame::Plain);
	scroll_area->setWidget(scroll_container);
	scroll_area->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
	scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scroll_container->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	scroll_container->setLayout(scroll_inner);

	QVBoxLayout::addWidget(scroll_area);
}

void CDScrollContainerLayout::addWidget(QWidget *widget) { scroll_inner->addWidget(widget); }

void CDScrollContainerLayout::removeWidget(QWidget *widget) { scroll_inner->removeWidget(widget); }
