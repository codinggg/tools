QT += core
QT += gui

CONFIG += c++11

QT += widgets


QT += serialport

TARGET = serialRW
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp \
    serial.cpp \
    form.cpp

HEADERS += \
    serial.h \
    form.h

FORMS += \
    form.ui
