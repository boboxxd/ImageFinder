#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T15:58:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageFinder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classfythread.cpp

HEADERS  += mainwindow.h \
    classfythread.h

FORMS    += mainwindow.ui
