#include "midistream.h"
#include <QMessageBox>

// Because connections are not made between MidiStream & the application yet, the application
// developer will need to manually load everything initially.  Once the signals and slots
// are connected, all changes should be made through the signals & slots.
MidiStream::MidiStream() : QObject() {
    #ifdef WIN
    #endif

    #ifdef COREAUDIO
    #endif

    #ifdef ALSA
    #endif

    #ifdef OSS
    #endif

    #ifdef JACK
        jackstream = new JackMidiStream();
        connect(jackstream, SIGNAL(send_event(Event*)), this, SLOT(incomingEvent(Event*)));
        connect(this, SIGNAL(send_event(Event*)), jackstream, SLOT(onJackOutgoingEvent(Event*)));
        input_ports.append(jackstream->loadInputPorts());
        output_ports.append(jackstream->loadOutputPorts());
    #endif
}


Port MidiStream::createPort(QString port_name, PutType iop, ConnectionType type) {
    Port p;
    #ifdef JACK
        if(type == jack) {
           p = jackstream->createPort(port_name, iop);
        }
    #endif

    return p;
}

int MidiStream::destroyPort(Port p) {
    return 0;
}

QList<Port> MidiStream::getInputPorts() {
    return input_ports;
}


QList<Port> MidiStream::getOutputPorts() {
    return output_ports;
}


int MidiStream::connectPort(Port ip, Port op) {
    return jackstream->connectPort(ip, op);

}


int MidiStream::disconnectPort(Port ip, Port op) {
    return jackstream->disconnectPort(ip, op);
}

Port MidiStream::getCurrentlyConnectedPort(Port p) {
    Port port;

    // Set up default in case we don't find it.
    port.port = NULL;
    port.name = QString();
    port.type = jack;

    #ifdef JACK
    if(p.type == jack) {
        port = jackstream->getCurrentlyConnectedPort(p);
    }
    #endif  // JACK

    return port;
}


void MidiStream::incomingEvent(Event *e) {
    emit send_message(QString("%1 %2 %3").arg(e->deltatime).arg(e->event).arg(e->params.at(0)));
}


void MidiStream::outgoingEvent(Event *e) {

}

// Currently, this will simply clear both lists of ports and get all the ports all over again.
// In the future, we will determine if this can be streamlined to only find the changes instead.
void MidiStream::portsChanged() {
    input_ports.clear();
    output_ports.clear();

#ifdef WIN
#endif

#ifdef COREAUDIO
#endif

#ifdef ALSA
#endif

#ifdef OSS
#endif

#ifdef JACK
    input_ports.append(jackstream->loadInputPorts());
    output_ports.append(jackstream->loadOutputPorts());
#endif

    // Let the program know they need to reload their ports
    emit ports_changed();
}
