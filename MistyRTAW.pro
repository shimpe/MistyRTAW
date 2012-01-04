#-------------------------------------------------
#
# Project created by QtCreator 2011-11-30T22:33:04
#
#-------------------------------------------------

QT       += core gui

TARGET = MistyRTAW

CONFIG += link_pkgconfig

PKGCONFIG = jack

win32 {
    DEFINES += __WINDOWS_MM__
    LIBS += -lwinmm
}

macx {
    DEFINES += __MACOSX_CORE__
    LIBS +=
}

unix {
    DEFINES += __LINUX_ALSASEQ__ \
               ALSA \
               JACK
    LIBS += -lasound
}

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    chordanalyzer.cpp \
    midifile.cpp \
    synthselector.cpp \
    mididata.cpp \
    midistream.cpp \
    jackmidistream.cpp \
    mistymidi.cpp

HEADERS  += \
    mainwindow.h \
    chordanalyzer.h \
    midifile.h \
    synthselector.h \
    mididata.h \
    midistream.h \
    jackmidistream.h \
    mistymidi.h

FORMS    += \
    mainwindow.ui \
    chordanalyzer.ui

RESOURCES += \
    MistyRTAW.qrc
