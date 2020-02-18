#-------------------------------------------------
#
# Project created by QtCreator 2018-09-28T08:37:50
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += multimedia
QT += multimediawidgets
TARGET = kiosk3
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig debug
PKGCONFIG += mpv

SOURCES += main.cpp \
    mpvwidget.cpp \
    alphaVideoPlayer.cpp \
    touchscreen.cpp \
    ledscreen.cpp \
    udplistener.cpp \
    powerLabel.cpp


HEADERS  += \
    mpvwidget.h \
    alphaVideoPlayer \
    alphaVideoPlayer.h \
    touchscreen.h \
    ledscreen.h \
    udplistener.h \
    powerLabel \
    powerLabel.h \
    positions.h


FORMS    +=


LIBS+=
