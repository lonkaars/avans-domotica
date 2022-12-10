#pragma once

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "mesh_connector.h"

/** @brief widget that displays single node */
class CDNodeWidget : public QWidget {
	Q_OBJECT

private:
	cd_s_node *_node = nullptr;
	cd_uid_t _id;

	QHBoxLayout *main_layout;
	QLabel *label_node_name;
	QLabel *label_node_address;
	QCheckBox *switch_on_off;
	QPushButton *button_add_remove;

public:
	CDNodeWidget(QWidget *parent = nullptr);
	virtual ~CDNodeWidget();
	/** @brief update node info in GUI */
	virtual void update();
	/** @brief register which node this widget controls */
	virtual void set_node(cd_uid_t id);
	/** @brief join/remove from network */
	virtual void toggle_provision();
	/** @brief turn led on/off */
	virtual void update_led(bool on);
};
