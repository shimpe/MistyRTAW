#include "mistymidi.h"
#include <QMessageBox>

MistyMidi::MistyMidi() : QObject() {
    mstream = new MidiStream();

    input_ports = mstream->getInputPorts();
    output_ports = mstream->getOutputPorts();

    misty_input_port = mstream->createPort("Input", inputtype, jack);
    misty_output_port.append(mstream->createPort("Piano", outputtype, jack));

    connect(mstream, SIGNAL(send_message(QString)), this, SLOT(receive_message(QString)));


}

int MistyMidi::getNumInputPorts() {
    return input_ports.size();
}

QString MistyMidi::getInputPortName(int port) {
    return input_ports.at(port)->name;
}

int MistyMidi::getNumOutputPorts() {
    return output_ports.size();
}

QString MistyMidi::getOutputPortName(int port) {
    return output_ports.at(port)->name;
}

Port* MistyMidi::getMistyInput() {
    return misty_input_port;
}

int   MistyMidi::numMistyOutputs() {
    return misty_output_port.size();
}

QList<Port *> MistyMidi::getMistyOutputs() {
    return misty_output_port;
}

void MistyMidi::receive_message(QString message) {
    emit send_message(message);
}

void MistyMidi::input_changed(QString port) {
    // Get Selected Input Port
    int i = 0;
    Port *p;

    // Disconnect current port (if it's connected)
    p = mstream->getCurrentlyConnectedPort(misty_input_port);
    if(p->port != NULL)
        mstream->disconnectPort(misty_input_port, p);


    // Connect to new port
    while (input_ports.at(i)->name != port) { i++; }
    if(input_ports.at(i)->name == port)
        p = input_ports.at(i);
    else {          // Since we're dealing with a preloaded set of identified outputs, we should never get here.
        QMessageBox qmb;
        qmb.setText(QString("Could not find %1").arg(port));
        qmb.exec();
    }

    int err = mstream->connectPort(misty_input_port, p);
}

void MistyMidi::output_changed(QString port) {

}

// This converts the numerical value of the note to a readable string.
QString MistyMidi::getNote(notes midinote) {
    return midi_note_converter.midiNoteToString(midinote);
}

