#ifndef MIDISTREAM_H
#define MIDISTREAM_H

#include <QObject>
#include <QString>

#include "mididata.h"

// MidiStream is the class that communicates between the hardware and/or other software programs.  The intent is to eventually flesh this out to handle
// All types of Audio systems in the most popular OS's (Win, MacOS, & Linux), thus the #ifdef's that currently don't do anything.  You will see these
// throughout the midistream.h & midistream.cpp files.  Initial coding will be for JACK, followed by ALSA.  After this will be determined by where we
// are at with the Misty app.

// Add appropriate #includes
#ifdef WIN
#endif

#ifdef COREAUDIO
#endif

#ifdef ALSA
#endif

#ifdef OSS
#endif

#ifdef JACK
    #include "jackmidistream.h"
#endif


class MidiStream : public QObject {
    Q_OBJECT
    public:
        MidiStream();
        QList<Port> getInputPorts();
        QList<Port> getOutputPorts();
        /*int openPort();
        int closePort();
        int numPorts();
        int getPort(); */
        Port createPort(QString port_name, PutType iop, ConnectionType type);
        int  destroyPort(Port p);
        int connectPort(Port ip, Port op);
        int disconnectPort(Port ip, Port op);
        Port getCurrentlyConnectedPort(Port p);
    signals:
        void send_message(QString message);
        void send_event(Event *e);
        void ports_changed();

    public slots:
        void incomingEvent(Event *e);
        void outgoingEvent(Event *e);
        void portsChanged();

    private:
        QList<Port> input_ports;
        QList<Port> output_ports;
        #ifdef JACK
            JackMidiStream *jackstream;
        #endif
};

#endif // MIDISTREAM_H
