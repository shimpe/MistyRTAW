#ifndef MIDI_H
#define MIDI_H

#include "RtMidi.h"
#include "RtError.h"
#include <QThread>
#include <string>


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

enum commands {
    note_off = 128,
    note_on = 144
};

class MIDI : public QThread
{
    Q_OBJECT
public:
    explicit MIDI(QObject *parent = 0);

    bool connect(QString connectName);
    void run();
    void stop();
    void loop();

signals:
    void send_message(QString message);

public slots:

private:
    bool connected;
    bool ok;
    RtMidiIn *midi_in;
    RtMidiOut *midi_out;
    QString getNote(unsigned int midinote);
};

/*
class MIDI_Out : public QThread
{
    Q_OBJECT
public:
    explicit MIDI_Out(QObject *parent = 0);

    bool connect(QString connectName);
    void run();
    void stop();
    void loop();

signals:
    void send_message(QString message);

public slots:

private:
    bool connected;
    bool ok;
    RtMidiOut *midi_out;
    QString getNote(unsigned int midinote);
};
*/

#endif // MIDI_H
