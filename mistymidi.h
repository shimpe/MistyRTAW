#ifndef MISTYMIDI_H
#define MISTYMIDI_H

#include "mididata.h"
#include "midistream.h"
#include "midinoteconverter.h"

class MistyMidi : public QObject
{
    Q_OBJECT
public:
    explicit MistyMidi();
    int getNumInputPorts();
    QString getInputPortName(int port);
    int getNumOutputPorts();
    QString getOutputPortName(int port);
    Port* getMistyInput();
    int   numMistyOutputs();
    QList<Port *> getMistyOutputs();
signals:
    void send_message(QString message);
public slots:
    void receive_message(QString message);
    void input_changed(QString port);
    void output_changed(QString port);
private:
    QString getNote(notes note);
    MidiStream *mstream;
    QList<Port *> input_ports;
    QList<Port *> output_ports;

    Port *misty_input_port;          // Misty is configured to only have one input port
    QList<Port *> misty_output_port;  // Misty is configured to have multiple output ports

    MidiNoteConverter midi_note_converter;
};

#endif // MISTYMIDI_H
