# -------------------------------------------------
# Project created by QtCreator 2010-02-16T14:42:47
# -------------------------------------------------
TARGET = PDFimpose
TEMPLATE = app
SOURCES += main.cpp \
    pdfimpose.cpp \
    itoa.cpp
HEADERS += pdfimpose.h \
    itoa.h
FORMS += pdfimpose.ui
INCLUDEPATH += /usr/include/poppler/qt4
LIBS += -L/usr/lib \
    -lpoppler-qt4
