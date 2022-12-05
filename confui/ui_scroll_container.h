#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>

class CDScrollContainerLayout : public QVBoxLayout {
	Q_OBJECT

private:
	QVBoxLayout* main_layout;
	QScrollArea* scroll_area;
	QWidget* scroll_container;
	QVBoxLayout* scroll_inner;

public:
	CDScrollContainerLayout(QWidget *parent = nullptr);
	virtual ~CDScrollContainerLayout();
	virtual void addWidget(QWidget* widget);
	virtual void removeWidget(QWidget* widget);
};

