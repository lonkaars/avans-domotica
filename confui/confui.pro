QT += core gui widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
		mesh_connector.cpp \
		ui_tab_automations.cpp \
		ui_tab_node_overview.cpp \
		ui_node.cpp \
		ui_automation.cpp

HEADERS += \
    mainwindow.h \
		mesh_connector.h \
		ui_tab_automations.h \
		ui_tab_node_overview.h \
		ui_node.h \
		ui_automation.h

CONFIG += c++17
CONFIG += force_debug_info

