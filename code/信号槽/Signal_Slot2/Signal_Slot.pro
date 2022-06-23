#-------------------------------------------------
#
# Project created by QtCreator 2022-03-24T15:37:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Signal_Slot
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    myclass1.cpp \
    myclass2.cpp

HEADERS  += widget.h \
    myclass1.h \
    myclass2.h

FORMS    += widget.ui
