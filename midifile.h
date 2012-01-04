#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QList>
#include "mididata.h"


class MidiFile : public QObject {
    Q_OBJECT

    public:
        MidiFile();
        int LoadFile(QString filename);     // Returns Error code
        QString getError(int error);        // Returns Error message based on Error code
        QString getEventName(quint8 eventnum);
        QString getNoteName(quint8 notenum);
        QString getMetaName(quint8 metanum);
        QString getSysExName(quint8 sysexnum);
        QString getTrackName(int tracknum);
        QString getTrackEvent(int tracknum, int eventnum);
        int     numTracks();
        int     numEvents(int tracknum);
    signals:
        void sendmessage(QString message);
    private:
        QList<Track *> track;
};

#endif // MIDIFILE_H
