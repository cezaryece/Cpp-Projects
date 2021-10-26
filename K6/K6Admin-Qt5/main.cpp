#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
    a.setApplicationName("Kanal6Admin");
	MainWindow w;
    w.setWindowTitle(a.applicationName() + "[" + QString(__DATE__) + " " + QString(__TIME__) + "]");
	w.show();
	
	return a.exec();
}
