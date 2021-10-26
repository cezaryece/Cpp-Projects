#-------------------------------------------------
#
# Project created by QtCreator 2011-01-12T13:47:10
#
#-------------------------------------------------

QT       += core network

#QT       -= gui

TARGET = SniffServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    sniffserver.cpp \
    sniffthread.cpp \
    sniff.cpp \
	../MY_LIBS/QTip.cpp

HEADERS += \
    sniffserver.h \
    sniffthread.h \
    sniff.h \
	../MY_LIBS/QTip.h \
    structs.h

LIBS += -lpcap \
    -Llibpcap \
	-lpfring \
	-L/usr/local/lib

INCLUDEPATH += /usr/include/sigc++-2.0 \
/usr/local/lib/libpcap \
../MY_LIBS \
	/usr/local/lib/libpf_ring
