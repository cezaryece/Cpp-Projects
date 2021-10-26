#-------------------------------------------------
#
# Project created by QtCreator 2011-01-26T10:48:10
#
#-------------------------------------------------

QT       += core gui network

TARGET = TSanalizer
TEMPLATE = app


SOURCES += main.cpp\
		tsanalizer.cpp \
../MY_LIBS/QTip.cpp

HEADERS  += tsanalizer.h \
    structs.h \
	TSstruct.h \
../MY_LIBS/QTip.h

FORMS    += tsanalizer.ui
