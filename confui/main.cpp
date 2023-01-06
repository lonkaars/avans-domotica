#include "main.h"
#include "mainwindow.h"

extern "C" {
static const uint16_t _test	 = 1;
static const uint8_t *_ptest = (uint8_t *)&_test;
uint8_t g_cd_endianness;
}

CDMainWindow* g_cd_main_window = nullptr;

int main(int argc, char *argv[]) {
	g_cd_endianness = *_ptest;
	g_cd_app = new QApplication(argc, argv);
	g_cd_main_window = new CDMainWindow();
	g_cd_main_window->show();
	return g_cd_app->exec();
}
