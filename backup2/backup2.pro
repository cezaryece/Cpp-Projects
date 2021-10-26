#-------------------------------------------------
#
# Project created by QtCreator 2013-04-15T09:07:42
#
#-------------------------------------------------

QT       += core sql
QT       -= gui
QMAKE_CXXFLAGS += -fopenmp
LIBS += -lgomp -fopenmp
TARGET = backup2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    config.cpp \
    tools.cpp \
    walker.cpp \
    mydatabase.cpp

HEADERS += \
    config.h \
    tools.h \
    walker.h \
    mydatabase.h

OTHER_FILES += \
    ../../../backup/backup.conf
