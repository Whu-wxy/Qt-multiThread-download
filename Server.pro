#-------------------------------------------------
#
# Project created by QtCreator 2019-07-30T16:50:59
#
#-------------------------------------------------

QT       += core gui
QT+=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloadFile.cpp \
    httpthread.cpp \
    downloaddata.cpp \
    downloadResources.cpp

HEADERS  += mainwindow.h \
    downloadFile.h \
    httpthread.h \
    downloaddata.h \
    downloadResources.h

FORMS    += mainwindow.ui
