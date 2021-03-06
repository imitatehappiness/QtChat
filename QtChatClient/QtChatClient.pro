#-------------------------------------------------
#
# Project created by QtCreator 2022-07-09T22:37:34
#
#-------------------------------------------------

QT += core gui
QT += network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtChatClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        authentication.cpp \
        main.cpp \
        client.cpp \
        registration.cpp \
        src/databaseaccessor.cpp \
        src/databasethread.cpp \
        settingmenu.cpp

HEADERS += \
        authentication.h \
        client.h \
        registration.h \
        src/include/databaseaccessor.h \
        src/include/databasethread.h \
        settingmenu.h \
        parameters.h

FORMS += \
        authentication.ui \
        client.ui \
        registration.ui \
        settingmenu.ui

RESOURCES += \
    style.qrc


OBJECTS_DIR = build/.obj

MOC_DIR = build/.moc

RCC_DIR = build/.rcc

UI_DIR = build/.ui

