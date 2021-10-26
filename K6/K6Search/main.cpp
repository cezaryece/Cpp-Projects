#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName("Kanal6 Szukaj");
	MainWindow w;
	w.setWindowTitle(a.applicationName());
	w.show();
	
	return a.exec();
}
