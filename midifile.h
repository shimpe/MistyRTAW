#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QList>
#include "midi.h"

enum errors {
    MidiFile_OK = 0,
    MidiFile_CannotOpen,
    MidiFile_NotAMidiFile,
    MidiFile_InvalidTrack,
    MidiFile_InvalidEvent,
    MidiFile_InvalidMeta,
    MidiFile_InvalidSysEx,
    MidiFile_InvalidMetaSysEx
};

enum chunkIDs {
    FileHeader = 0x4d546864,
    TrackHeader  = 0x4d54726B
};

enum events {
    event_note_off    = 0x80,
    event_note_on     = 0x90,
    event_note_at     = 0xA0,  // Note Aftertouch
    event_controller  = 0xB0,
    event_prog_change = 0xC0,  // Program Change
    event_chan_at     = 0xD0,  // Channel Aftertouch
    event_pitch_bend  = 0xE0,
    event_meta        = 0xF0
};

enum metatypes {
    meta_sequence     = 0x00,
    meta_text         = 0x01,
    meta_copyright    = 0x02,
    meta_seqtrackname = 0x03,
    meta_instname     = 0x04,
    meta_lyrics       = 0x05,
    meta_marker       = 0x06,
    meta_cuepoint     = 0x07,
    meta_channel      = 0x20,
    meta_endoftrack   = 0x2F,
    meta_settempo     = 0x51,
    meta_smpteoffset  = 0x54,
    meta_timesig      = 0x58,
    meta_keysig       = 0x59,
    meta_seqspecific  = 0x7F
};

enum sysextypes {

};

class Event {
    public:
        Event();
        quint32 deltatime;   // This holds the time to wait until the next event
        quint8  event;       // This byte holds both event type or meta/sysEx identification (first 4 bits) & channel, meta, or sysEx event types (last 4 bits)
        QList<quint8> params;
};

class Track {
    public:
        Track();
        QList<Event *> event;
};

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
