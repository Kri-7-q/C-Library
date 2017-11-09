#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T19:31:32
#
#-------------------------------------------------

QT       -= gui

TARGET = Console
TEMPLATE = lib

DEFINES += CONSOLE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += optiondefinition.cpp \
    optionparser.cpp \
    consoleuserinterface.cpp \
    colorbool.cpp \
    tableheader.cpp \
    columnheader.cpp \
    Exception/interfaceexception.cpp \
    consolefont.cpp

HEADERS += console_global.h \
    optiondefinition.h \
    optionparser.h \
    consoleuserinterface.h \
    colorbool.h \
    tableheader.h \
    columnheader.h \
    Exception/interfaceexception.h \
    consolefont.h

# ---------------------------------------------------------
# Make install (distinguish between debug and release).
# ---------------------------------------------------------
unix {
    headers.files = $$HEADERS
    headers.path = /usr/local/include/Console
    CONFIG(release, debug|release) {
        target.path = /usr/local/lib/Console/Release
    }
    CONFIG(debug, debug|release) {
        target.path = /usr/local/lib/Console/Debug
    }
    INSTALLS += target headers
}
