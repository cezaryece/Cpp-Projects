#-------------------------------------------------
#
# Project created by QtCreator 2010-10-20T09:52:32
#
#-------------------------------------------------

QT       += core gui

TARGET = pckt_analizer
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    itoa.cpp

HEADERS  += dialog.h \
    pckt_handler.h \
    itoa.h

FORMS    += dialog.ui
LIBS += -lpcap \
	-Llibpcap \
	-lpfring \
	-Llibpfring
INCLUDEPATH += /usr/include/sigc++-2.0 \
	/usr/local/lib/libpcap \
	/usr/local/lib/libpfring
