#-------------------------------------------------
#
# Project created by QtCreator 2011-11-28T11:22:24
#
#-------------------------------------------------

QT       += core gui

TARGET = RTMidiTest

win32 {
    DEFINES += __WINDOWS_MM__
    LIBS += -lwinmm
}

macx {
    DEFINES += __MACOSX_CORE__
    LIBS +=
}

unix {
    DEFINES += __LINUX_ALSASEQ__
    LIBS += -lasound
}

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    RtMidi.cpp \
    midi.cpp

HEADERS  += mainwindow.h \
    RtError.h \
    RtMidi.h \
    midi.h

FORMS    += mainwindow.ui
