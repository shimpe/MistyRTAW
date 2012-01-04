// JackMidiStream handles all the interactions with the JACK server.  All JACK events are
// received through this class and then transmitted using signals to the MidiStream class,
// which will route the event appropriately back to the application.

#ifdef JACK

    #ifndef JACKMIDISTREAM_H
    #define JACKMIDISTREAM_H


    #include <jack/jack.h>
    #include <jack/midiport.h>
    #include "mididata.h"

    #include <QObject>
    #include <QList>

    class JackMidiStream : public QObject {
        Q_OBJECT
    public:
        explicit JackMidiStream();
        bool ok();
        QList<Port *> loadInputPorts();
        QList<Port *> loadOutputPorts();
        Port* createPort(QString port_name, PutType iop);
        int  destroyPort(QString port_id);
        int connectPort(Port *ip, Port *op);
        int disconnectPort(Port *ip, Port *op);
        Port* getCurrentlyConnectedPort(Port *p);
        // Callback Functions
        static int  onReceiveEvent(jack_nframes_t nframes, void *arg);
        static void onJackShutdown(void *arg);

    signals:
        void send_event(Event *e);  // This is for sending MIDI events only.
        void send_message(QString message);

    public slots:
        void onJackIncomingEvent(Port *p);
        void onJackOutgoingEvent(jack_nframes_t nframes, Port *p);

    protected:
        jack_client_t *jack_client;
        QList<Port *> internal_input_port;
        QList<Port *> internal_output_port;
        QList<Port *> external_input_port;
        QList<Port *> external_output_port;


        // Boolean operators identify whether or not all JACK functions were performed
        // Successfully, so we know whether or not it's ok to attempt to send data.
        // This is because signals are not connected during instance constructor, so we have
        // no reporting mechanisms yet.
        bool opened;
        bool activated;
    };

    #endif // JACKMIDISTREAM_H
#endif // JACK
