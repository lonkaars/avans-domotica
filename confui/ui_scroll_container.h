#pragma once

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

/** @brief generic vertically scrolling layout */
class CDScrollContainerLayout : public QVBoxLayout {
	Q_OBJECT

private:
	QVBoxLayout *main_layout;
	QScrollArea *scroll_area;
	QWidget *scroll_container;
	QVBoxLayout *scroll_inner;

public:
	CDScrollContainerLayout(QWidget *parent = nullptr);
	virtual ~CDScrollContainerLayout();
	/** @brief add widget to layout */
	virtual void addWidget(QWidget *widget);
	/** @brief remove widget from layout */
	virtual void removeWidget(QWidget *widget);
};
