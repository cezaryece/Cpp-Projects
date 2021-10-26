QT += multimedia multimediawidgets
QT       += widgets sql network webkitwidgets 

#CONFIG   += console
CONFIG   += app_bundle
TARGET = Kanal6Admin
TEMPLATE = app

HEADERS = \
    videoplayer.h

SOURCES = \
    main.cpp \
    videoplayer.cpp

INSTALLS += target

QT+=widgets
