// This is a temporary class used to test output from the MidiFile being piped to
// MidiStream output.  It is not intended to remain as part of the final code.

// This class is a separate thread that keeps checking the port buffer to see how many
// items it has left in the buffer.  If the buffer has less than 3 items left,
// this will add another loop of the track to the buffer to ensure there is always something
// to play.

#include "testmidioutput.h"

#define MINNUMEVENTSLEFT 3

TestMidiOutput::TestMidiOutput(QList<Port *> output_ports, MidiFile *mf) : QThread() {
    ports = output_ports;
    midi = mf;
}


void TestMidiOutput::run() {
    emit send_message("TMO Run...");
    running = true;
    int i, j;

    while(running) {
        emit send_message("In While Loop");
        emit send_message(QString("# Ports: %1  Tracks: %2").arg(ports.size()).arg(midi->numTracks()));
        for(i = 0; i < midi->numTracks(); i++) {
            if(ports.at(i)->out_buffer.size() < MINNUMEVENTSLEFT) {
                emit send_message(QString("TMO: Adding %1 events to output buffer").arg(midi->numEvents(i)));
                for(j=0; j < midi->numEvents(i); j++) {
                    emit send_message(QString("i = %1, j = %2").arg(i).arg(j));
                    ports.at(i)->out_buffer.append(midi->getTrackEvent(i, j));
                    emit send_message(QString("TMO Sending Event: %1").arg(midi->getTrackEventText(i, j)));
                }
            }  // else move on to the next track
        }
        msleep(10);
    }
}

void TestMidiOutput::stop() {
    emit send_message("TMO Stop");
    running = false;
}
