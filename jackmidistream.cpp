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
    if(!internal_input_port.isEmpty())  internal_input_port.clear();
    if(!internal_output_port.isEmpty()) internal_output_port.clear();
    if(!external_input_port.isEmpty())  external_input_port.clear();
    if(!external_output_port.isEmpty()) external_output_port.clear();
}

bool JackMidiStream::ok() {
    if (opened && activated)
        return true;
    else return false;
}


// This loads the list of External Input ports that application can access
QList<Port *> JackMidiStream::loadInputPorts() {
    Port *p;
    const char **jack_port;

    jack_port = jack_get_ports(jack_client, NULL, JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput);

    unsigned int i = 0;
    while (jack_port[i] != NULL) {
        p = new Port();
        p->port = jack_port_by_name(jack_client, jack_port[i]);
        p->name = QString(jack_port[i]);
        p->iop  = inputtype;
        p->type = jack;
        p->out_buffer.clear();

        external_input_port.append(p);
        i++;
    }

    free(jack_port);
    return external_input_port;
}


QList<Port *> JackMidiStream::loadOutputPorts() {
    Port *p;
    const char **jack_port;

    jack_port = jack_get_ports(jack_client, NULL, JACK_DEFAULT_MIDI_TYPE, JackPortIsInput);

    unsigned int i = 0;
    while (jack_port[i] != NULL) {
        p = new Port();
        p->port = jack_port_by_name(jack_client, jack_port[i]);
        p->name = QString(jack_port[i]);
        p->iop  = outputtype;
        p->type = jack;
        p->out_buffer.clear();

        external_output_port.append(p);
        i++;
    }
    free(jack_port);
    return external_output_port;
}


// Create a port in which app is the owner
Port* JackMidiStream::createPort(QString port_name, PutType iop) {
    Port *p = new Port();

    if(iop == inputtype) {
        p->port = jack_port_register(jack_client, port_name.toAscii(), JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);

        if(p->port == NULL) {
            p->name      = QString("None");
            p->iop       = iop;
            p->type      = jack;
            p->in_buffer = NULL;
            p->out_buffer.clear();
        } else {
            p->name      = jack_port_name((jack_port_t *)p->port);
            p->iop       = iop;
            p->type      = jack;
            p->in_buffer = NULL;
            p->out_buffer.clear();
        }
        internal_input_port.append(p);
    } else {
        p->port = jack_port_register(jack_client, port_name.toAscii(), JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

        if(p->port == NULL) {
            p->name      = QString("None");
            p->iop       = iop;
            p->type      = jack;
            p->in_buffer = NULL;
            p->out_buffer.clear();
        } else {
            p->name      = jack_port_name((jack_port_t *)p->port);
            p->iop       = iop;
            p->type      = jack;
            p->in_buffer = NULL;
            p->out_buffer.clear();
        }
        internal_output_port.append(p);
    }

    return p;
}


int JackMidiStream::destroyPort(QString port_id) {
    return 0;
}

// ip = input, op = output
int JackMidiStream::connectPort(Port *ip, Port *op) {
    return jack_connect(jack_client, op->name.toAscii(), ip->name.toAscii());
}


// ip = input, op = output
int JackMidiStream::disconnectPort(Port *ip, Port *op) {
    return jack_disconnect(jack_client, op->name.toAscii(), ip->name.toAscii());
}


Port* JackMidiStream::getCurrentlyConnectedPort(Port *p) {
    const char **port;
    Port *returnport = new Port();

    port = jack_port_get_connections((jack_port_t *)p->port);

    if(port==NULL) {
        returnport->port   = NULL;
        returnport->name   = QString();
        returnport->type   = jack;
        returnport->out_buffer.clear();
    } else {
        returnport->port   = jack_port_by_name(jack_client, port[0]);
        returnport->name   = QString(port[0]);
        returnport->type   = jack;
        returnport->out_buffer.clear();
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
    for (int i=0; i < ms->internal_input_port.size(); i++) {
        buffer = jack_port_get_buffer((jack_port_t *)ms->internal_input_port.at(i)->port, nframes);

        if(jack_midi_get_event_count(buffer) > 0)
            ms->internal_input_port.at(i)->in_buffer = buffer;
            ms->onJackIncomingEvent(ms->internal_input_port.at(i));
    }

    for (int j=0; j < ms->internal_output_port.size(); j++) {
        if(!ms->internal_output_port.at(j)->out_buffer.isEmpty()) {
            ms->onJackOutgoingEvent(nframes, ms->internal_output_port.at(j));
        }
    }
    return 0;
}


void JackMidiStream::onJackIncomingEvent(Port *p) {
    jack_midi_event_t jack_event;
    Event *ms_event;

    for(unsigned int i=0; i < jack_midi_get_event_count(p->in_buffer); i++) {
        jack_midi_event_get(&jack_event, p->in_buffer, i);
        ms_event = new Event();

        ms_event->deltatime = jack_event.time;
        ms_event->event = *(jack_event.buffer);

        unsigned int j = 1;
        do {
            ms_event->params.append(*(jack_event.buffer + j));
        } while (j++ < jack_event.size);
        emit send_event(ms_event);
        emit send_message(QString("JMS Sending Event: %1 %2").arg(ms_event->deltatime).arg(ms_event->event));
    }
}


void JackMidiStream::onJackOutgoingEvent(jack_nframes_t nframes, Port *p) {
    unsigned int i;  // loop trackers
    unsigned char *buffer;  // Staging buffer between p->port & output_buffer

    // Prep output buffer
    void *output_buffer  = jack_port_get_buffer((jack_port_t *)p->port, nframes);
    jack_midi_clear_buffer(output_buffer);

    // Pull event for processing
        Event *e = p->out_buffer.first();
        p->out_buffer.removeFirst();

        for(i=0; i < nframes; i++) {
            if(e->deltatime == i) {
                switch(e->event) {
                    case event_note_on:
                    case event_note_off:
                    case event_note_at:
                        buffer = jack_midi_event_reserve(output_buffer, i, 3);
                        buffer[0] = e->event;
                        buffer[1] = e->params.at(0);
                        buffer[2] = e->params.at(1);
                        break;
                    default:    // Currently, we're only supporting note on, off, at.
                        break;  // Everything else will be ignored.
                }
            }
        }
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
