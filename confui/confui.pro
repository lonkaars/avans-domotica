QT += core gui widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
		mesh_connector.cpp \
		ui_tab_automations.cpp \
		ui_tab_node_overview.cpp \
		ui_node.cpp \
		ui_automation.cpp \
		ui_scroll_container.cpp

HEADERS += \
    mainwindow.h \
		mesh_connector.h \
		ui_tab_automations.h \
		ui_tab_node_overview.h \
		ui_node.h \
		ui_automation.h \
		ui_scroll_container.h

CONFIG += c++17
CONFIG += force_debug_info

