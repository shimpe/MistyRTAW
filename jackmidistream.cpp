#ifdef JACK
#include "jackmidistream.h"
#include <QMessageBox>

JackMidiStream::JackMidiStream() : QObject() {
    opened = true;
    activated = true;  // Assume we connected just fine, unless we didn't.

    // Attempt to connect to JACK server
    if((jack_client = jack_client_open("Misty", JackNullOption, NULL))==0) {
        opened = false;
    } else {
        // Assign Callback functions
        jack_on_shutdown(jack_client, onJackShutdown, this);
        jack_set_process_callback(jack_client, onReceiveEvent, this);

        // Attempt to Activate the JACK client
        if(jack_activate(jack_client)) {
            activated = false;
        }
    }
}

bool JackMidiStream::ok() {
    if (opened && activated)
        return true;
    else return false;
}


QList<Port> JackMidiStream::loadInputPorts() {
    Port p;
    const char **jack_port;
    QList<Port> ports;

    jack_port = jack_get_ports(jack_client, NULL, JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput);

    unsigned int i = 0;
    while (jack_port[i] != NULL) {
        p.port = jack_port_by_name(jack_client, jack_port[i]);
        p.name = QString(jack_port[i]);
        p.type = jack;

        ports.append(p);
        i++;
    }

    free(jack_port);
    return ports;
}


QList<Port> JackMidiStream::loadOutputPorts() {
    Port p;
    const char **jack_port;
    QList<Port> ports;

    jack_port = jack_get_ports(jack_client, NULL, JACK_DEFAULT_MIDI_TYPE, JackPortIsInput);

    unsigned int i = 0;
    while (jack_port[i] != NULL) {
        p.port = jack_port_by_name(jack_client, jack_port[i]);
        p.name = QString(jack_port[i]);
        p.type = jack;

        ports.append(p);
        i++;
    }
    free(jack_port);
    return ports;
}


Port JackMidiStream::createPort(QString port_name, PutType iop) {
    Port p;

    //jack_deactivate(jack_client);

    if(iop == inputtype) {
        p.port = jack_port_register(jack_client, port_name.toAscii(), JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
        inputs.append(p);
    } else {
        p.port = jack_port_register(jack_client, port_name.toAscii(), JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
        outputs.append(p);
    }

    if(p.port == NULL) {
        p.name = QString();
        p.type = jack;
    } else {
        p.name = jack_port_name((jack_port_t *)p.port);
        p.type = jack;
    }

    //jack_activate(jack_client);

    return p;
}


int JackMidiStream::destroyPort(QString port_id) {
    return 0;
}

// ip = input, op = output
int JackMidiStream::connectPort(Port ip, Port op) {
    return jack_connect(jack_client, op.name.toAscii(), ip.name.toAscii());
}


// ip = input, op = output
int JackMidiStream::disconnectPort(Port ip, Port op) {
    return jack_disconnect(jack_client, op.name.toAscii(), ip.name.toAscii());
}


Port JackMidiStream::getCurrentlyConnectedPort(Port p) {
    QMessageBox qmb;

    const char **port;
    Port returnport;

    if(p.port==NULL) { qmb.setText("Port's port is null"); qmb.exec(); }
    else { qmb.setText(jack_port_name((jack_port_t *)p.port)); qmb.exec(); }

    port = jack_port_get_connections((jack_port_t *)p.port);

    if(port==NULL) {
        qmb.setText("Port[0] == NULL");
        qmb.exec();
        returnport.port = NULL;
        returnport.name = QString();
        returnport.type = jack;
    } else {
        returnport.port = jack_port_by_name(jack_client, port[0]);
        returnport.name = QString(port[0]);
        returnport.type = jack;
    }

    free(port);
    return returnport;
}


// This is a callback function for C, so it must be static.  Invoked from jack_set_process_callback
// void *arg = the pointer back to our class instance, so we can emit signals.
int JackMidiStream::onReceiveEvent(jack_nframes_t nframes, void *arg) {
    JackMidiStream *ms = (JackMidiStream *)arg;
    void *buffer;

    // The concept for this function is basic:  When we're told to process something,
    // Review all input and output ports to see if there's something to do on each.
    for (int i=0; i < ms->inputs.size(); i++) {
        buffer = jack_port_get_buffer((jack_port_t *)ms->inputs.at(i).port, nframes);

        if(jack_midi_get_event_count(buffer) > 0)
            ms->onJackIncomingEvent(buffer, arg);
    }

    return 0;
}


void JackMidiStream::onJackIncomingEvent(void *buffer, void *arg) {
    jack_midi_event_t jack_event;
    Event *ms_event;

    for(unsigned int i=0; i < jack_midi_get_event_count(buffer); i++) {
        jack_midi_event_get(&jack_event, buffer, i);
        ms_event = new Event();

        ms_event->deltatime = jack_event.time;
        ms_event->event = *(jack_event.buffer);

        unsigned int j = 1;
        do {
            ms_event->params.append(*(jack_event.buffer + j));
        } while (j++ < jack_event.size);
        emit send_event(ms_event);
    }
}


void JackMidiStream::onJackOutgoingEvent(Event *e) {

}


// This is a callback function for C, so it must be static.  Invoked from jack_on_shutdown
// void *arg = the pointer back to our class instance, so we can emit signals.
void JackMidiStream::onJackShutdown(void *arg) {
    JackMidiStream *ms = (JackMidiStream *)arg;
    emit ms->send_message("JACK Server has shut down.");

    ms->opened = false;
    ms->activated = false;
}

#endif  // JACK
