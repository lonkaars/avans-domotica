QT += core gui widgets serialport

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	mesh_connector.cpp \
	ui_tab_automations.cpp \
	ui_tab_node_overview.cpp \
	ui_node.cpp \
	ui_automation.cpp \
	ui_scroll_container.cpp \
	serial.cpp \
	../shared/bin.c \
	../shared/protocol.c \
	../shared/serial_parse.c \
	../shared/pclient.c

HEADERS += \
	mainwindow.h \
	mesh_connector.h \
	ui_tab_automations.h \
	ui_tab_node_overview.h \
	ui_node.h \
	ui_automation.h \
	ui_scroll_container.h \
	serial.h \
	../shared/bin.h \
	../shared/protocol.h \
	../shared/serial_parse.h \
	../shared/consts.h \
	main.h \
	../shared/pclient.h

CONFIG += c++17
CONFIG += force_debug_info
QMAKE_CXXFLAGS += -Wno-missing-field-initializers
QMAKE_CFLAGS += -std=c11
QMAKE_CFLAGS += -Wno-c99-designator

DEFINES += CD_MALLOC=malloc
DEFINES += CD_FREE=free
