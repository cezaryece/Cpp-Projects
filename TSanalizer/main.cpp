#include <QtGui/QApplication>
#include "tsanalizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TsAnalizer w;
    w.show();

    return a.exec();
}
