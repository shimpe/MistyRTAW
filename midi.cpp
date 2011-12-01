#include "midi.h"


MIDI::MIDI(QObject *parent) : QThread(parent) {
    connected = false;
    ok = false;
    midi_in = NULL;
    midi_out = NULL;
}

bool MIDI::connect(QString connectName) {
    ok = true;  // Assume this is going to work.  If it doesn't work, it'll get caught, and
                // ok will be changed right back to false.
    try {
        midi_in = new RtMidiIn(connectName.toStdString());
    } catch (RtError &err) {
        emit send_message(QString("Error Loading: %1").arg(err.getMessage().c_str()));
        ok = false;
    }

    try {
        midi_out = new RtMidiOut(connectName.toStdString());
    } catch (RtError &err) {
        emit send_message(QString("Error Loading: %1").arg(err.getMessage().c_str()));
        ok = false;
    }

    if(ok) {
        emit send_message(QString("%1 input ports found:").arg(midi_in->getPortCount()));

        for(unsigned int i=0;i<midi_in->getPortCount(); i++) {
            emit send_message(QString("%1").arg(midi_in->getPortName(i).c_str()));
        }

        emit send_message(QString("\n%1 output ports found:").arg(midi_out->getPortCount()));

        for(unsigned int i=0;i<midi_out->getPortCount(); i++) {
            emit send_message(QString("%1").arg(midi_out->getPortName(i).c_str()));
        }
    }

    return ok;
}

void MIDI::run() {
    bool ok = true;  // If any errors occur, this will be changed to false.
    std::string errmsg;

    if(!connected) {   // If we are not yet connected...
        if(ok) {        // And midi_in has been successfully created...
            midi_in->openVirtualPort("Input");
            midi_out->openVirtualPort("Output");
            emit send_message("Connected.");
            connected = true;

            loop();  // Start the loop
        } else emit send_message("Connect failed.");  // If not connected but midi_in not successfully created
    } else {
        emit send_message("Cannot Connect: Already connected");  // If already connected...
    }
}

void MIDI::stop() {
    delete midi_in;
    delete midi_out;
    connected = false;
    emit send_message("Disconnected.");
}

void MIDI::loop() {
    double time;
    std::vector<unsigned char> message;

    while(connected) {
        time = midi_in->getMessage(&message);

        if(message.size() > 0) {
            switch(message.at(0)) {
                case note_on:   // Note On
                    emit send_message(QString("%1: Note On, %2.  Velocity %3").arg(time).arg(getNote(message.at(1))).arg(message.at(2)));
                    break;
                case note_off:   // Note Off, ignore velocity
                    emit send_message(QString("%1: Note Off, %2").arg(time).arg(getNote(message.at(1))));
                    break;
                default:
                    emit send_message(QString("%1: Other Command").arg(time));
                    for(unsigned int i=0; i<message.size(); i++) {
                        emit send_message(QString("%1").arg(message.at(i)));
                    }
                    break;
            }

            midi_out->sendMessage(&message);
        }
    }
}

// This converts the numerical value of the note to a readable string.  Due to the number
// of notes in MIDI, it's pretty long.
QString MIDI::getNote(unsigned int midinote) {
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

/*
MIDI_Out::MIDI_Out(QObject *parent) : QThread(parent) {
    connected = false;
    ok = false;
    midi_out = NULL;
}

bool MIDI_Out::connect(QString connectName) {
    ok = true;  // Assume this is going to work.  If it doesn't work, it'll get caught, and
                // ok will be changed right back to false.
    try {
        midi_out = new RtMidiOut(connectName.toStdString());
    } catch (RtError &err) {
        emit send_message(QString("Error Loading: %1").arg(err.getMessage().c_str()));
        ok = false;
    }
    if(ok) {
        emit send_message(QString("%1 ports found:").arg(midi_out->getPortCount()));

        for(unsigned int i=0;i<midi_out->getPortCount(); i++) {
            emit send_message(QString("%1").arg(midi_out->getPortName(i).c_str()));
        }
    }

    return ok;
}

void MIDI_Out::run() {

}

void MIDI_Out::stop() {

}

void MIDI_Out::loop() {

}
*/
