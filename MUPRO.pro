#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T20:50:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MUPRO
TEMPLATE = app


SOURCES += main.cpp\
        mupromain.cpp \
    ferroinput.cpp \
    effectivepropertyinput.cpp \
    phasetab.cpp \
    patternreco.cpp

HEADERS  += mupromain.h \
    ferroinput.h \
    effectivepropertyinput.h \
    phasetab.h \
    patternreco.h

FORMS    += mupromain.ui \
    ferroinput.ui \
    effectivepropertyinput.ui \
    phasetab.ui \
    patternreco.ui

RESOURCES += \
    mupro-resource.qrc
