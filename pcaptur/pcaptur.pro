# -------------------------------------------------
# Project created by QtCreator 2009-11-30T12:42:09
# -------------------------------------------------
QT -= core \
    gui
TARGET = pcaptur
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    pcap_handler.cpp \
    ../MY_LIBS/bytewrite/bytewrite.cpp \
    ../MY_LIBS/str_replace/str_replace.cpp \
    ../MY_LIBS/unspace.cpp \
    ../MY_LIBS/str_explode.cpp
HEADERS += pcap_handler.h \
    ../MY_LIBS/bytewrite/bytewrite.h \
    ../MY_LIBS/str_replace/str_replace.h \
    ../MY_LIBS/unspace.h \
    ../MY_LIBS/str_explode.h
INCLUDEPATH += /usr/lib/libpcap-1.0.0 \
    /usr/lib/libpf_ring \
    /home/czarek/Dokumenty/SVN/programowanie/MY_LIBS
LIBS += -lpcap \
    -L/usr/lib/ \
    -lpfring \
    -L/usr/lib/
