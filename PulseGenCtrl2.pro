#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T12:39:52
#
#-------------------------------------------------

QT       += core gui serialport widgets

#include(c:/qt/4.8.5/src/serialport/qt4support/serialport.prf)

TARGET = PulseGenCtrl2
TEMPLATE = app


SOURCES += main.cpp \
    PulseGenCtrl2.cpp \
    bSpinBoxWidget.cpp

HEADERS  += PulseGenCtrl2.h \
            bSpinBoxWidget.h \
    ui_bSpinBoxWidget.h

RC_FILE = PulseGenCtrl2.rc

RESOURCES += \
    icons.qrc

FORMS += bSpinBoxWidget.ui

OTHER_FILES += down_arrow.svg \
          up_arrow.svg

DISTFILES += \
    ../../../../svn/PulseGenCtrl2/PulseGenCtrl.ico
