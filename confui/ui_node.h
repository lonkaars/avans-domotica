#pragma once

#include <QWidget>

#include "mesh_connector.h"

class CDNodeWidget : public QWidget {
	Q_OBJECT

private:
	cd_s_node* _node;

public:
	CDNodeWidget(cd_s_node* node, QWidget *parent = nullptr);
	virtual ~CDNodeWidget();
};
