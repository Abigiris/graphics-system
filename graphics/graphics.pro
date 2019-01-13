#-------------------------------------------------
#
# Project created by QtCreator 2018-12-01T08:46:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shape.cpp \
    oval.cpp \
    circle.cpp \
    curve.cpp \
    line.cpp \
    pen.cpp \
    poly.cpp \
    rect.cpp \
    fill.cpp \
    window.cpp \
    fillrect.cpp \
    fillcircle.cpp \
    filloval.cpp

HEADERS  += mainwindow.h \
    shape.h \
    line.h \
    curve.h \
    rect.h \
    oval.h \
    circle.h \
    pen.h \
    poly.h \
    fill.h \
    window.h \
    fillrect.h \
    fillcircle.h \
    filloval.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
