#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T21:38:18
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minesProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myitem.cpp \
    mydialog.cpp \
    connectwidget.cpp \
    infoDialog.cpp

HEADERS  += mainwindow.h \
    myitem.h \
    mydialog.h \
    connectwidget.h \
    infoDialog.h

RESOURCES += \
    images.qrc \
    music.qrc

FORMS += \
    infoDialog.ui
