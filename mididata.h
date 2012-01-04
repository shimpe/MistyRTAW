#ifndef MIDIDATA_H
#define MIDIDATA_H

#include <QObject>
#include <QList>

//  N = Negative, s = Sharp.  Flats will not be denoted.
enum notes {
    CN1 = 0, CsN1, DN1, DsN1, EN1, FN1, FsN1, GN1, GsN1,
    A0, As0, B0, C0, Cs0, D0, Ds0, E0, F0, Fs0, G0, Gs0,
    A1, As1, B1, C1, Cs1, D1, Ds1, E1, F1, Fs1, G1, Gs1,
    A2, As2, B2, C2, Cs2, D2, Ds2, E2, F2, Fs2, G2, Gs2,
    A3, As3, B3, C3, Cs3, D3, Ds3, E3, F3, Fs3, G3, Gs3,
    A4, As4, B4, C4, Cs4, D4, Ds4, E4, F4, Fs4, G4, Gs4,
    A5, As5, B5, C5, Cs5, D5, Ds5, E5, F5, Fs5, G5, Gs5,
    A6, As6, B6, C6, Cs6, D6, Ds6, E6, F6, Fs6, G6, Gs6,
    A7, As7, B7, C7, Cs7, D7, Ds7, E7, F7, Fs7, G7, Gs7,
    A8, As8, B8, C8, Cs8, D8, Ds8, E8, F8, Fs8, G8, Gs8,
    A9, As9, B9, C9, Cs9, D9, Ds9, E9, F9, Fs9, G9
};

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

// SysEx Currently not supported, but planned in the future.
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


enum ConnectionType {
    windows = 0,
    coreaudio,
    alsa,
    oss,
    jack
};


// Used to identify if a port being created is input or output
enum PutType {
    inputtype = 0,
    outputtype
};

class Port {
public:
    Port();
    const void *port;
    QString name;
    PutType iop;
    ConnectionType type;
    void *in_buffer;
    QList<Event *> out_buffer;  // Used to transfer events to output
};

#endif // MIDIDATA_H
