// Class MidiFile represents reading data from a .mid file and does not have any function with transmitting MIDI data to other programs/MIDI hardware.


#include "midifile.h"

Event::Event() {
    deltatime = 0;
    event     = 0;
    if(!params.empty())
        params.clear();
}


Track::Track() {
    if(!event.empty())
        event.clear();
}


MidiFile::MidiFile() {
}

int MidiFile::LoadFile(QString filename) {
    quint32 fileheader, filelength;  // These five variables are used for
    quint16 fileformat, filetracks;  //  the header chunk exclusively.
    qint16  filedivision;         //

    Event *newevent;
    Track *newtrack;

    quint32 trackheader, tracklength;   // The header & track length (in bytes) aren't needed beyond reading in the file, so no need adding to Track class.

    quint8 dtseg;    // Temp variable to read in delta time
    quint8 eventseg; // Temp variable to read in event parameters


    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        return MidiFile_CannotOpen;
    }

    QDataStream in(&file);

    in >> fileheader;

    if(fileheader != FileHeader) {          // If what we read doesn't match what it's supposed to be...
        return MidiFile_NotAMidiFile;
    }

    in >> filelength >> fileformat >> filetracks >> filedivision;


    // Read In Tracks
    for(quint16 i = 0; i<filetracks; i++) {
        newtrack = new Track();
        in >> trackheader;

        if(trackheader != TrackHeader) {
            return MidiFile_InvalidTrack;
        }

        in >> tracklength;

        // Due to variable lengths and various sizes depending on the incoming messages, and the length of the track, we cannot do a for loop.
        // We must keep track of how much length of the track we have left, we will decrement it as we pull each byte.
        while (tracklength > 0) {
            newevent = new Event();

            do {                        // Assemble Delta Time
                in >> dtseg;
                newevent->deltatime = (newevent->deltatime << 7) + (dtseg & 0x7F);
            } while (dtseg & 0x80); // If greater than 127, then there are additional bits to take


            in >> newevent->event;    // This byte holds both event type or meta/sysEx identification (first 4 bits) & channel, meta, or sysEx event types (last 4 bits)
            switch (newevent->event & 0xF0) {   // Determine action based on event type
                case note_on:
                    in >> eventseg;                             // note
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // velocity
                    newevent->params.append(eventseg);
                    break;
                case note_off:
                    in >> eventseg;                             // note
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // velocity
                    newevent->params.append(eventseg);
                    break;
                case note_at:
                    in >> eventseg;                             // note
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // amount
                    newevent->params.append(eventseg);
                    break;
                case controller:
                    in >> eventseg;                             // controller type
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // value
                    newevent->params.append(eventseg);
                    break;
                case prog_change:
                    in >> eventseg;                             // New Program #
                    newevent->params.append(eventseg);
                    break;
                case chan_at:
                    in >> eventseg;                             // amount
                    newevent->params.append(eventseg);
                    break;
                case pitch_bend:
                    in >> eventseg;                             // Value (LSB)
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // Value (MSB)
                    newevent->params.append(eventseg);
                    break;
                case meta:                                      // This section handles both meta & sysEx messages, as both events start w/ 0xF
                    switch(newevent->event & 0x0F) {            // The second set of 4 bits identifies meta vs. sysex, which will define how we deal with the parameters.
                        case 0xF:               // meta
                            in >> eventseg;                     // Meta Event Type
                            newevent->params.append(eventseg);

                            in >> dtseg;             // Length - typically we use eventseg, but we need eventseg to read in during the for loop,
                                                                 // and dtseg's not being used at the moment.
                            newevent->params.append(dtseg);

                            for(int i=0; i< dtseg; i++) {
                                in >> eventseg;

                                newevent->params.append(eventseg);
                            }
                            break;

                        case 0x0:               // sysEx
                        case 0x7:
                            in >> eventseg;                     // Meta Event Type
                            newevent->params.append(eventseg);

                            in >> dtseg;             // Length - typically we use eventseg, but we need eventseg to read in during the for loop,
                                                             // and dtseg's not being used at the moment.
                            newevent->params.append(dtseg);

                            for(int i=0; i< dtseg; i++) {
                                in >> eventseg;

                                newevent->params.append(eventseg);
                            }
                            break;
                        default:
                            return MidiFile_InvalidMetaSysEx;
                            break;
                    }
                    break;
                default:
                    return MidiFile_InvalidEvent;
                    break;
            }
        }
    }
    return MidiFile_OK;
}

QString MidiFile::getError(int error) {
    QString message;

    switch(error) {
        case MidiFile_OK:
            message = "No error.";
            break;
        case MidiFile_CannotOpen:
            message = "Error: Cannot open requested file.";
            break;
        case MidiFile_NotAMidiFile:
            message = "Error: Requested file is not a valid MIDI file.";
            break;
        case MidiFile_InvalidTrack:
            message = "Error: A Track did not load successfully.  The MIDI file may be corrupted.";
            break;
        case MidiFile_InvalidEvent:
            message = "Error:  An Event was not recongized.  The MIDI file may be corrupted.";
            break;
        case MidiFile_InvalidMeta:
            message = "Error: A Meta Event was not recognized.  The MIDI file may be corrupted.";
            break;
        case MidiFile_InvalidSysEx:
            message = "Error:  A SysEx Event was not recognized.  The MIDI file may be corrupted.";
            break;
        case MidiFile_InvalidMetaSysEx:
            message = "Error:  A Meta/SysEx Event was not recognized.  The Midi file may be corrupted.";
            break;
        default:
            message = QString("No error message defined for Error Code %1.  Please log an issue at https://github.com/MistyRTAW/MistyRTAW/issues").arg(error);
            break;
    }

    return message;
}
