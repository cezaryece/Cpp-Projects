#-------------------------------------------------
#
# Project created by QtCreator 2013-02-07T08:28:51
#
#-------------------------------------------------

QT       += core gui sql network phonon webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG   += console
CONFIG   += app_bundle

TARGET = Kanal6Admin
TEMPLATE = app
SOURCES += main.cpp\
		mainwindow.cpp \
	fileutils.cpp \
    newsgroupbox.cpp \
    programgroupbox.cpp \
    gbbase.cpp \
    fotkawidget.cpp \
    listform.cpp \
    videoform.cpp \
    logindialog.cpp \
    chartable.cpp \
    characterwidget.cpp \
    searchgroupbox.cpp
HEADERS  += mainwindow.h \
	fileutils.h \
	uploader.h \
    newsgroupbox.h \
    programgroupbox.h \
    gbbase.h \
    fotkawidget.h \
    listform.h \
    videoform.h \
    logindialog.h \
    chartable.h \
    characterwidget.h \
    searchgroupbox.h

FORMS += \
	mainwindow.ui \
    newsgroupbox.ui \
    programgroupbox.ui \
    fotkawidget.ui \
    listform.ui \
    videoform.ui \
    logindialog.ui \
    chartable.ui \
    searchgroupbox.ui
RC_FILE = k6admin.rc
RESOURCES += textedit.qrc

OTHER_FILES += \
    images/win/zoomout.png \
    images/win/zoomin.png \
    images/win/textunder.png \
    images/win/textright.png \
    images/win/textleft.png \
    images/win/textjustify.png \
    images/win/textitalic.png \
    images/win/textcenter.png \
    images/win/textbold.png \
    images/win/filesave.png \
    images/win/fileprint.png \
    images/win/fileopen.png \
    images/win/filenew.png \
    images/win/exportpdf.png \
    images/win/editundo.png \
    images/win/editredo.png \
    images/win/editpaste.png \
    images/win/editcut.png \
    images/win/editcopy.png \
    images/win/media-playback-start.png \
    images/win/media-playback-pause.png \
    images/win/media-eject.png \
    images/win/insert-image.png \
    images/win/image-x-generic.png \
    k6admin.rc

