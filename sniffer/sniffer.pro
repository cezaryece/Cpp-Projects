# -------------------------------------------------
# Project created by QtCreator 2009-09-22T11:19:49
# -------------------------------------------------
QT -= gui
TARGET = sniffer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    pckt_handler.cpp \
    init.cpp \
    demonize.cpp
LIBS += -lpcap \
    -lpfring
INCLUDEPATH += /usr/include/sigc++-2.0 \
    /usr/local/lib/libpcap \
    /usr/local/lib/libpf_ring
HEADERS += pckt_handler.h \
    init.h \
    demonize.h
