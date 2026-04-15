#-------------------------------------------------
#
# Project created by QtCreator 2020-02-04T23:59:47
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PDFReader_Qt
TEMPLATE = app

# Relative Path based on .pro file.
SOURCES += main.cpp\
        mainwindow.cpp \
    util.cpp

HEADERS  += mainwindow.h \
    util.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../../../include/

# Relative Path based on generated file.
contains(QT_ARCH, i386) {
    LIBS += -L../../../lib -lfsdk_linux32
} else {
    LIBS += -L../../../lib -lfsdk_linux64
}
UI_DIR = ./temp/ui
MOC_DIR = ./temp/moc
OBJECTS_DIR = ./temp/objs
RCC_DIR = ./temp/rcc

DESTDIR = ./bin



QMAKE_CXXFLAGS += -std=c++0x
CONFIG += C++11

RESOURCES += \
    icons.qrc
