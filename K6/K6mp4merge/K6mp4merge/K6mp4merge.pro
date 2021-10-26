#-------------------------------------------------
#
# Project created by QtCreator 2014-05-21T13:23:50
#
#-------------------------------------------------

QT       += core gui phonon sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = K6mp4merge
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    walker.cpp

HEADERS  += mainwindow.h \
    walker.h

FORMS    += mainwindow.ui

RC_FILE = k6admin.rc
RESOURCES += textedit.qrc
OTHER_FILES += \
	images/zoomout.png \
	images/zoomin.png \
	images/textunder.png \
	images/textright.png \
	images/textleft.png \
	images/textjustify.png \
	images/textitalic.png \
	images/textcenter.png \
	images/textbold.png \
	images/filesave.png \
	images/fileprint.png \
	images/fileopen.png \
	images/filenew.png \
	images/exportpdf.png \
	images/editundo.png \
	images/editredo.png \
	images/editpaste.png \
	images/editcut.png \
	images/editcopy.png \
	images/media-playback-start.png \
	images/media-playback-pause.png \
	images/media-eject.png \
	images/insert-image.png \
	images/image-x-generic.png \
	k6admin.rc
