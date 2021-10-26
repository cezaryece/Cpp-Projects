# -------------------------------------------------
# Project created by QtCreator 2009-11-27T09:23:03
# -------------------------------------------------
QT -= core \
    gui
TARGET = multicast
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    pckt_handler.cpp \
    init.cpp \
    demonize.cpp \
    str_replace.cpp \
    bytewrite.cpp \
    itoa.cpp
LIBS += -lpcap \
    -L/usr/lib/ \
    -lglibmm-2.4 \
    -L/usr/lib \
    -lpfring \
    -L/usr/lib/
INCLUDEPATH += /usr/include/glibmm-2.4 \
    /usr/include/glib-2.0 \
    /usr/include/sigc++-2.0 \
    /usr/lib/libpcap-1.0.0 \
    /usr/lib/libpf_ring
HEADERS += pckt_handler.h \
    init.h \
    demonize.h \
    str_replace.h \
    bytewrite.h \
    itoa.h
FORMS += dialog.ui
