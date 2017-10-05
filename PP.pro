#-------------------------------------------------
#
# Project created by Rafał Mazurkiewicz 2017-09-20T12:10:47
#
#-------------------------------------------------

QT       += core gui
QT       += core
QT       += sql widgets
RC_FILE = myapp.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectDB.cpp

HEADERS  += mainwindow.h \
    connectDB.h \
    version.h

FORMS    += mainwindow.ui

RESOURCES +=

DISTFILES += \
    myapp.rc
