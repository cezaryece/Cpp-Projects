#include <QtGui/QApplication>
#include "fcwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FCWindow w;
    w.show();
    return a.exec();
}
