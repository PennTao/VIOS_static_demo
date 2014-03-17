#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T15:27:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VIOS_static_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygraphicsview.cpp \
    mygraphicsscene.cpp \
    socketcomm.cpp \
    xmldataparser.cpp \
    frame.cpp

HEADERS  += mainwindow.h \
    mygraphicsview.h \
    mygraphicsscene.h \
    socketcomm.h \
    xmldataparser.h \
    frame.h

FORMS    += mainwindow.ui

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
