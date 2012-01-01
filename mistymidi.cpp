#include "mistymidi.h"
#include <QMessageBox>

MistyMidi::MistyMidi() : QObject() {
    mstream = new MidiStream();

    input_ports = mstream->getInputPorts();
    output_ports = mstream->getOutputPorts();

    misty_input_port = mstream->createPort("Input", inputtype, jack);
    connect(mstream, SIGNAL(send_message(QString)), this, SLOT(receive_message(QString)));
}

int MistyMidi::getNumInputPorts() {
    return input_ports.size();
}

QString MistyMidi::getInputPortName(int port) {
    return input_ports.at(port).name;
}

int MistyMidi::getNumOutputPorts() {
    return output_ports.size();
}

QString MistyMidi::getOutputPortName(int port) {
    return output_ports.at(port).name;
}

void MistyMidi::receive_message(QString message) {
    emit send_message(message);
}

void MistyMidi::input_changed(QString port) {
    // Get Selected Input Port
    int i = 0;
    Port p;
    Port temp;

    QMessageBox qmb;

    // Disconnect current port (if it's connected)
    p = mstream->getCurrentlyConnectedPort(misty_input_port);
    if(p.port != NULL)
        mstream->disconnectPort(misty_input_port, p);


    // Connect to new port
    while (input_ports.at(i).name != port) { i++; }
    if(input_ports.at(i).name == port)
        p = input_ports.at(i);
    else {          // Since we're dealing with a preloaded set of identified outputs, we should never get here.
//        QMessageBox qmb;
        qmb.setText(QString("Could not find %1").arg(port));
        qmb.exec();
    }

    int err = mstream->connectPort(misty_input_port, p);
    qmb.setText(QString("Error #%1: %2 %3").arg(err, 0, 16).arg(misty_input_port.name).arg(p.name));
    qmb.exec();
}

void MistyMidi::output_changed(QString port) {

}

// This converts the numerical value of the note to a readable string.  Due to the number
// of notes in MIDI, it's pretty long.
QString MistyMidi::getNote(notes midinote) {
    QString note;

    switch(midinote) {
        case CN1:  note = "C-1";  break;
        case CsN1: note = "C#-1"; break;
        case DN1:  note = "D-1";  break;
        case DsN1: note = "D#-1"; break;
        case EN1:  note = "E-1";  break;
        case FN1:  note = "F-1";  break;
        case FsN1: note = "F#-1"; break;
        case GN1:  note = "G-1";  break;
        case GsN1: note = "G#-1"; break;

        case A0:  note = "A0";  break;
        case As0: note = "A#0"; break;
        case B0:  note = "B0";  break;
        case C0:  note = "C0";  break;
        case Cs0: note = "C#0"; break;
        case D0:  note = "D0";  break;
        case Ds0: note = "D#0"; break;
        case E0:  note = "E0";  break;
        case F0:  note = "F0";  break;
        case Fs0: note = "F#0"; break;
        case G0:  note = "G0";  break;
        case Gs0: note = "G#0"; break;

        case A1:  note = "A1";  break;
        case As1: note = "A#1"; break;
        case B1:  note = "B1";  break;
        case C1:  note = "C1";  break;
        case Cs1: note = "C#1"; break;
        case D1:  note = "D1";  break;
        case Ds1: note = "D#1"; break;
        case E1:  note = "E1";  break;
        case F1:  note = "F1";  break;
        case Fs1: note = "F#1"; break;
        case G1:  note = "G1";  break;
        case Gs1: note = "G#1"; break;

        case A2:  note = "A2";  break;
        case As2: note = "A#2"; break;
        case B2:  note = "B2";  break;
        case C2:  note = "C2";  break;
        case Cs2: note = "C#2"; break;
        case D2:  note = "D2";  break;
        case Ds2: note = "D#2"; break;
        case E2:  note = "E2";  break;
        case F2:  note = "F2";  break;
        case Fs2: note = "F#2"; break;
        case G2:  note = "G2";  break;
        case Gs2: note = "G#2"; break;

        case A3:  note = "A3";  break;
        case As3: note = "A#3"; break;
        case B3:  note = "B3";  break;
        case C3:  note = "C3";  break;
        case Cs3: note = "C#3"; break;
        case D3:  note = "D3";  break;
        case Ds3: note = "D#3"; break;
        case E3:  note = "E3";  break;
        case F3:  note = "F3";  break;
        case Fs3: note = "F#3"; break;
        case G3:  note = "G3";  break;
        case Gs3: note = "G#3"; break;

        case A4:  note = "A4";  break;
        case As4: note = "A#4"; break;
        case B4:  note = "B4";  break;
        case C4:  note = "C4";  break;
        case Cs4: note = "C#4"; break;
        case D4:  note = "D4";  break;
        case Ds4: note = "D#4"; break;
        case E4:  note = "E4";  break;
        case F4:  note = "F4";  break;
        case Fs4: note = "F#4"; break;
        case G4:  note = "G4";  break;
        case Gs4: note = "G#4"; break;

        case A5:  note = "A5";  break;
        case As5: note = "A#5"; break;
        case B5:  note = "B5";  break;
        case C5:  note = "C5";  break;
        case Cs5: note = "C#5"; break;
        case D5:  note = "D5";  break;
        case Ds5: note = "D#5"; break;
        case E5:  note = "E5";  break;
        case F5:  note = "F5";  break;
        case Fs5: note = "F#5"; break;
        case G5:  note = "G5";  break;
        case Gs5: note = "G#5"; break;

        case A6:  note = "A6";  break;
        case As6: note = "As6"; break;
        case B6:  note = "B6";  break;
        case C6:  note = "C6";  break;
        case Cs6: note = "C#6"; break;
        case D6:  note = "D6";  break;
        case Ds6: note = "D#6"; break;
        case E6:  note = "E6";  break;
        case F6:  note = "F6";  break;
        case Fs6: note = "F#6"; break;
        case G6:  note = "G6";  break;
        case Gs6: note = "G#6"; break;

        case A7:  note = "A7";  break;
        case As7: note = "A#7"; break;
        case B7:  note = "B7";  break;
        case C7:  note = "C7";  break;
        case Cs7: note = "C#7"; break;
        case D7:  note = "D7";  break;
        case Ds7: note = "D#7"; break;
        case E7:  note = "E7";  break;
        case F7:  note = "F7";  break;
        case Fs7: note = "F#7"; break;
        case G7:  note = "G7";  break;
        case Gs7: note = "G#7"; break;

        case A8:  note = "A8";  break;
        case As8: note = "As8"; break;
        case B8:  note = "B8";  break;
        case C8:  note = "C8";  break;
        case Cs8: note = "C#8"; break;
        case D8:  note = "D8";  break;
        case Ds8: note = "D#8"; break;
        case E8:  note = "E8";  break;
        case F8:  note = "F8";  break;
        case Fs8: note = "F#8"; break;
        case G8:  note = "G8";  break;
        case Gs8: note = "G#8"; break;

        case A9:  note = "A9";  break;
        case As9: note = "As9"; break;
        case B9:  note = "B9";  break;
        case C9:  note = "C9";  break;
        case Cs9: note = "C#9"; break;
        case D9:  note = "D9";  break;
        case Ds9: note = "D#9"; break;
        case E9:  note = "E9";  break;
        case F9:  note = "F9";  break;
        case Fs9: note = "F#9"; break;
        case G9:  note = "G9";  break;

        default:  note = "Error:  Note not found."; break;
    }

    return note;
}
