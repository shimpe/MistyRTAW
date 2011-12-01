#-------------------------------------------------
#
# Project created by QtCreator 2011-11-30T22:33:04
#
#-------------------------------------------------

QT       += core gui

TARGET = MistyRTAW

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

SOURCES += main.cpp \
    midi.cpp \
    mainwindow.cpp \
    RtMidi.cpp

HEADERS  += \
    mainwindow.h \
    midi.h \
    RtError.h \
    RtMidi.h

FORMS    += \
    mainwindow.ui








