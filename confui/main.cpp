#include "main.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
	g_cd_app = new QApplication(argc, argv);
	CDMainWindow w;
	w.show();
	return g_cd_app->exec();
}
