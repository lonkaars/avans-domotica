QT += core gui widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
		mesh_connector.cpp \
		ui_automations.cpp \
		ui_node_overview.cpp \
		ui_node.cpp

HEADERS += \
    mainwindow.h \
		mesh_connector.h \
		ui_automations.h \
		ui_node_overview.h \
		ui_node.h

CONFIG += c++17
CONFIG += force_debug_info

