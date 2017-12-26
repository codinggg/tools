#-------------------------------------------------
#
# Project created by QtCreator 2017-08-21T14:18:36
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = serialSwitch
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QT      += serialport

SOURCES += main.cpp \
    serial.cpp

HEADERS += \
    serial.h
