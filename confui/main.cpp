#include "main.h"
#include "mainwindow.h"

extern "C" {
static const uint16_t _test	 = 1;
static const uint8_t *_ptest = (uint8_t *)&_test;
uint8_t g_cd_endianness;
}

int main(int argc, char *argv[]) {
	g_cd_endianness = *_ptest;
	g_cd_app = new QApplication(argc, argv);
	CDMainWindow w;
	w.show();
	return g_cd_app->exec();
}
