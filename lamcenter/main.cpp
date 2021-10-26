#include <QtGui/QApplication>
#include "window.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window  * w;
    int res=1;
    while (res) {
        w = new Window;
        w->show();
        res = a.exec();
        delete w;
    }
}
