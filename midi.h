#ifndef MIDI_H
#define MIDI_H

#include "RtMidi.h"
#include "RtError.h"
#include <QThread>
#include <string>
#include "mididata.h"


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
    void add_input(QString input);
    void add_output(QString output);

public slots:
    void outputMidiEvent(Event *event);

private:
    bool connected;
    bool ok;
    RtMidiIn *midi_in;
    RtMidiOut *midi_out;
    QString getNote(unsigned int midinote);
};

#endif // MIDI_H
