#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T20:50:58
#
#-------------------------------------------------

QT       += core gui
 QT += printsupport
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = MUPRO
TEMPLATE = app


SOURCES += main.cpp\
        mupromain.cpp \
    ferroinput.cpp \
    effectivepropertyinput.cpp \
    phasetab.cpp \
    patternreco.cpp \
    magnetic.cpp \
    generatebatch.cpp \
    view.cpp \
    batch.cpp

HEADERS  += mupromain.h \
    ferroinput.h \
    effectivepropertyinput.h \
    phasetab.h \
    patternreco.h \
    magnetic.h \
    generatebatch.h \
    view.h \
    batch.h

FORMS    += mupromain.ui \
    ferroinput.ui \
    effectivepropertyinput.ui \
    phasetab.ui \
    patternreco.ui \
    magnetic.ui \
    generatebatch.ui \
    view.ui \
    batch.ui

RESOURCES += \
    mupro-resource.qrc

DISTFILES += \
    ../../../../../Desktop/Screen Shot 2016-08-12 at 1.33.09 AM.png
