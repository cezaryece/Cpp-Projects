#include <QtGui/QApplication>
#include "pdfimpose.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PDFimpose w;
    w.show();
    return a.exec();
}
