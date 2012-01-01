// Class MidiFile represents reading data from a .mid file and does not have any function with transmitting MIDI data to other programs/MIDI hardware.

#include "midifile.h"


MidiFile::MidiFile() : QObject() {
    if(!track.isEmpty()) track.clear();
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

    int result = MidiFile_OK;
    bool endoftrack;

    QFile file(QString("%1/%2/%3").arg(QDir::currentPath()).arg(QString("MIDI")).arg(filename));
    if(!file.open(QIODevice::ReadOnly)) {
        return MidiFile_CannotOpen;
    }

    QDataStream in(&file);

    in >> fileheader;

    if(fileheader != FileHeader) {          // If what we read doesn't match what it's supposed to be...
        //file.close();
        return MidiFile_NotAMidiFile;
    }

    in >> filelength >> fileformat >> filetracks >> filedivision;
    emit sendmessage(QString("%1 Length: %2, # Tracks: %3, File Division: %4").arg(fileheader, 0, 16).arg(filelength).arg(filetracks).arg(filedivision));

    // Read In Tracks
    for(quint16 i = 0; i<filetracks; i++) {
        newtrack = new Track();
        endoftrack = false;
        in >> trackheader;

        if(trackheader != TrackHeader) {
            //file.close();
            return MidiFile_InvalidTrack;
        }

        in >> tracklength;
        emit sendmessage(QString("%1 Track Length: %2").arg(tracklength, 0, 16).arg(tracklength));
        // Due to variable lengths and various sizes depending on the incoming messages, and the length of the track, we cannot do a for loop.
        // We must keep track of how much length of the track we have left, we will decrement it as we pull each byte.
        while (!endoftrack) {
            newevent = new Event();

            do {                        // Assemble Delta Time
                in >> dtseg;
                newevent->deltatime = (newevent->deltatime << 7) + (dtseg & 0x7F);
            } while (dtseg & 0x80); // If greater than 127, then there are additional bits to take


            in >> newevent->event;    // This byte holds both event type or meta/sysEx identification (first 4 bits) & channel, meta, or sysEx event types (last 4 bits)

            switch (newevent->event & 0xF0) {   // Determine action based on event type
                case event_note_on:
                    in >> eventseg;                             // note
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // velocity
                    newevent->params.append(eventseg);
                    emit sendmessage(QString("%1: %2 on Channel %3; Note: %4  Velocity %5").arg(newevent->deltatime).arg(getEventName(newevent->event)).arg(newevent->event & 0x0F).arg(getNoteName(newevent->params.at(0))).arg(newevent->params.at(1)));
                    break;
                case event_note_off:
                    in >> eventseg;                             // note
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // velocity
                    newevent->params.append(eventseg);
                    emit sendmessage(QString("%1: %2 on Channel %3; Note: %4  Velocity %5").arg(newevent->deltatime).arg(getEventName(newevent->event)).arg(newevent->event & 0x0F).arg(getNoteName(newevent->params.at(0))).arg(newevent->params.at(1)));
                    break;
                case event_note_at:
                    in >> eventseg;                             // note
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // amount
                    newevent->params.append(eventseg);
                    emit sendmessage(QString("%1: %2 on Channel %3; Note: %4  Velocity %5").arg(newevent->deltatime).arg(getEventName(newevent->event)).arg(newevent->event & 0x0F).arg(getNoteName(newevent->params.at(0))).arg(newevent->params.at(1)));
                    break;
                case event_controller:
                    in >> eventseg;                             // controller type
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // value
                    newevent->params.append(eventseg);
                    emit sendmessage(QString("%1: %2 on Channel %3; Type: %4  Value: %5").arg(newevent->deltatime).arg(getEventName(newevent->event)).arg(newevent->event & 0x0F).arg(newevent->params.at(0)).arg(newevent->params.at(1)));
                    break;
                case event_prog_change:
                    in >> eventseg;                             // New Program #
                    newevent->params.append(eventseg);
                    emit sendmessage(QString("%1: %2 to #%3 on Channel %4").arg(newevent->deltatime).arg(getEventName(newevent->event)).arg(newevent->params.at(0)).arg(newevent->event & 0x0F));
                    break;
                case event_chan_at:
                    in >> eventseg;                             // amount
                    newevent->params.append(eventseg);
                    emit sendmessage(QString("%1: %2 on Channel %3: %4").arg(newevent->deltatime).arg(getEventName(newevent->event)).arg(newevent->event & 0x0F).arg(newevent->params.at(0)));
                    break;
                case event_pitch_bend:
                    in >> eventseg;                             // Value (LSB)
                    newevent->params.append(eventseg);
                    in >> eventseg;                             // Value (MSB)
                    newevent->params.append(eventseg);
                    emit sendmessage(QString("%1: %2 on Channel %3: %4").arg(newevent->deltatime).arg(getEventName(newevent->event)).arg(newevent->event & 0x0F).arg((newevent->params.at(1)<<7)+(newevent->params.at(0)<<7)));
                    break;
                case event_meta:                                      // This section handles both meta & sysEx messages, as both events start w/ 0xF
                    switch(newevent->event & 0x0F) {            // The second set of 4 bits identifies meta vs. sysex, which will define how we deal with the parameters.
                        case 0xF:               // meta
                            in >> eventseg;                     // Meta Event Type
                            newevent->params.append(eventseg);

                            in >> dtseg;             // Length - typically we use eventseg, but we need eventseg to read in during the for loop,
                                                                 // and dtseg's not being used at the moment.
                            newevent->params.append(dtseg);
                            emit sendmessage(QString("META %1, Length: %2").arg(getMetaName(newevent->params.at(0))).arg(dtseg));

                            if(newevent->params.at(0) != meta_endoftrack) {
                                emit sendmessage("Parameters:");
                                for(int i=0; i< dtseg; i++) {
                                    in >> eventseg;

                                    newevent->params.append(eventseg);
                                    emit sendmessage(QString("  %1").arg(eventseg));
                                }
                            } else { endoftrack = true; }
                            break;

                        case 0x0:               // sysEx
                        case 0x7:
                            emit sendmessage("SysEx message: Currently Ignored.");
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
                            emit sendmessage(QString("%1:  Not meta or sysex.").arg(newevent->event &0x0F));
                            return MidiFile_InvalidMetaSysEx;
                            break;
                    }
                    break;
                default:
                    emit sendmessage(QString("%1 is not a valid event").arg(newevent->event, 0, 16));
                    return MidiFile_InvalidEvent;
                    break;
            }
        }
    }
    file.close();
    return result;
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

QString MidiFile::getEventName(quint8 eventnum) {
    QString result;
    switch (eventnum) {
        case event_note_on:
        result = "Note On";
            break;
        case event_note_off:
            result = "Note Off";
            break;
        case event_note_at:
            result = "Note Aftertouch";
            break;
        case event_controller:
            result = "Controller";
            break;
        case event_prog_change:
            result = "Program Change";
            break;
        case event_chan_at:
            result = "Channel Aftertouch";
            break;
        case event_pitch_bend:
            result = "Pitch Bend";
            break;
        case event_meta:
            result = "Meta/SysEx";
            break;
        default:
            result = QString("Event %1 not found.").arg(eventnum, 0, 16);
            break;
    }
    return result;
}

QString MidiFile::getNoteName(quint8 notenum) {
    QString note;

    switch(notenum) {
        case CN1:  note = "C-1";  break;
        case CsN1: note = "C#/Db-1"; break;
        case DN1:  note = "D-1";  break;
        case DsN1: note = "D#/Eb-1"; break;
        case EN1:  note = "E-1";  break;
        case FN1:  note = "F-1";  break;
        case FsN1: note = "F#/Gb-1"; break;
        case GN1:  note = "G-1";  break;
        case GsN1: note = "G#/Ab-1"; break;

        case A0:  note = "A0";  break;
        case As0: note = "A#/Bb0"; break;
        case B0:  note = "B0";  break;
        case C0:  note = "C0";  break;
        case Cs0: note = "C#/Db0"; break;
        case D0:  note = "D0";  break;
        case Ds0: note = "D#/Eb0"; break;
        case E0:  note = "E0";  break;
        case F0:  note = "F0";  break;
        case Fs0: note = "F#/Gb0"; break;
        case G0:  note = "G0";  break;
        case Gs0: note = "G#/Ab0"; break;

        case A1:  note = "A1";  break;
        case As1: note = "A#/Bb1"; break;
        case B1:  note = "B1";  break;
        case C1:  note = "C1";  break;
        case Cs1: note = "C#/Db1"; break;
        case D1:  note = "D1";  break;
        case Ds1: note = "D#/Eb1"; break;
        case E1:  note = "E1";  break;
        case F1:  note = "F1";  break;
        case Fs1: note = "F#/Gb1"; break;
        case G1:  note = "G1";  break;
        case Gs1: note = "G#/Ab1"; break;

        case A2:  note = "A2";  break;
        case As2: note = "A#/Bb2"; break;
        case B2:  note = "B2";  break;
        case C2:  note = "C2";  break;
        case Cs2: note = "C#/Db2"; break;
        case D2:  note = "D2";  break;
        case Ds2: note = "D#/Eb2"; break;
        case E2:  note = "E2";  break;
        case F2:  note = "F2";  break;
        case Fs2: note = "F#/Gb2"; break;
        case G2:  note = "G2";  break;
        case Gs2: note = "G#/Ab2"; break;

        case A3:  note = "A3";  break;
        case As3: note = "A#/Bb3"; break;
        case B3:  note = "B3";  break;
        case C3:  note = "C3";  break;
        case Cs3: note = "C#/Db3"; break;
        case D3:  note = "D3";  break;
        case Ds3: note = "D#/Eb3"; break;
        case E3:  note = "E3";  break;
        case F3:  note = "F3";  break;
        case Fs3: note = "F#/Gb3"; break;
        case G3:  note = "G3";  break;
        case Gs3: note = "G#/Ab3"; break;

        case A4:  note = "A4";  break;
        case As4: note = "A#/Bb4"; break;
        case B4:  note = "B4";  break;
        case C4:  note = "C4";  break;
        case Cs4: note = "C#/Db4"; break;
        case D4:  note = "D4";  break;
        case Ds4: note = "D#/Eb4"; break;
        case E4:  note = "E4";  break;
        case F4:  note = "F4";  break;
        case Fs4: note = "F#/Gb4"; break;
        case G4:  note = "G4";  break;
        case Gs4: note = "G#/Ab4"; break;

        case A5:  note = "A5";  break;
        case As5: note = "A#/Bb5"; break;
        case B5:  note = "B5";  break;
        case C5:  note = "C5";  break;
        case Cs5: note = "C#/Db5"; break;
        case D5:  note = "D5";  break;
        case Ds5: note = "D#/Eb5"; break;
        case E5:  note = "E5";  break;
        case F5:  note = "F5";  break;
        case Fs5: note = "F#/Gb5"; break;
        case G5:  note = "G5";  break;
        case Gs5: note = "G#/Ab5"; break;

        case A6:  note = "A6";  break;
        case As6: note = "A#/Bb6"; break;
        case B6:  note = "B6";  break;
        case C6:  note = "C6";  break;
        case Cs6: note = "C#/Db6"; break;
        case D6:  note = "D6";  break;
        case Ds6: note = "D#/Eb6"; break;
        case E6:  note = "E6";  break;
        case F6:  note = "F6";  break;
        case Fs6: note = "F#/Gb6"; break;
        case G6:  note = "G6";  break;
        case Gs6: note = "G#/Ab6"; break;

        case A7:  note = "A7";  break;
        case As7: note = "A#/Bb7"; break;
        case B7:  note = "B7";  break;
        case C7:  note = "C7";  break;
        case Cs7: note = "C#/Db7"; break;
        case D7:  note = "D7";  break;
        case Ds7: note = "D#/Eb7"; break;
        case E7:  note = "E7";  break;
        case F7:  note = "F7";  break;
        case Fs7: note = "F#/Gb7"; break;
        case G7:  note = "G7";  break;
        case Gs7: note = "G#/Ab7"; break;

        case A8:  note = "A8";  break;
        case As8: note = "A#/Bb8"; break;
        case B8:  note = "B8";  break;
        case C8:  note = "C8";  break;
        case Cs8: note = "C#/Db8"; break;
        case D8:  note = "D8";  break;
        case Ds8: note = "D#/Eb8"; break;
        case E8:  note = "E8";  break;
        case F8:  note = "F8";  break;
        case Fs8: note = "F#/Gb8"; break;
        case G8:  note = "G8";  break;
        case Gs8: note = "G#/Ab8"; break;

        case A9:  note = "A9";  break;
        case As9: note = "A#/Bb9"; break;
        case B9:  note = "B9";  break;
        case C9:  note = "C9";  break;
        case Cs9: note = "C#/Db9"; break;
        case D9:  note = "D9";  break;
        case Ds9: note = "D#/Eb9"; break;
        case E9:  note = "E9";  break;
        case F9:  note = "F9";  break;
        case Fs9: note = "F#/Gb9"; break;
        case G9:  note = "G9";  break;

        default:  note = QString("Error:  Note #%1 not found.").arg(notenum, 0, 16); break;
    }
    return note;
}

QString MidiFile::getMetaName(quint8 metanum) {
    QString metaname;
    switch(metanum) {
    case meta_sequence:
        metaname = "Sequence";
        break;
    case meta_text:
        metaname = "Text";
        break;
    case meta_copyright:
        metaname = "Copyright";
        break;
    case meta_seqtrackname:
        metaname = "Track Name";
        break;
    case meta_instname:
        metaname = "Instrument Name";
        break;
    case meta_lyrics:
        metaname = "Lyrics";
        break;
    case meta_marker:
        metaname = "Marker";
        break;
    case meta_cuepoint:
        metaname = "Cue Point";
        break;
    case meta_channel:
        metaname = "Channel";
        break;
    case meta_endoftrack:
        metaname = "End Of Track";
        break;
    case meta_settempo:
        metaname = "Set Tempo";
        break;
    case meta_smpteoffset:
        metaname = "SMPTE Offset";
        break;
    case meta_timesig:
        metaname = "Time Signature";
        break;
    case meta_keysig:
        metaname = "Key Signature";
        break;
    case meta_seqspecific:
        metaname = "Sequencer Specific";
        break;
    default:
        metaname = QString("Meta %1 not found.").arg(metanum, 0, 16);
        break;
    }
    return metaname;
}

QString MidiFile::getSysExName(quint8 sysexnum) {
    Q_UNUSED(sysexnum);  // SysEx is not anticipated to be used for this program.  This function is here in case decision to implement in the future is made.
    return QString("SysEx Lookups not currently available.");
}

QString MidiFile::getTrackName(int tracknum) {
    Track *search_track = track.at(tracknum);
    int i = 0; int j = 0;
    bool ok = false;
    QString result;

    while (!ok && i < search_track->event.count()) {
        if(search_track->event.at(i)->event == event_meta) {
            if(search_track->event.at(i)->params.at(0) == meta_seqtrackname) {
                ok = true;   //  We found what we're looking for.  Break out.

                while(j++ < search_track->event.at(i)->params.count()) {
                    result.append(QString("%1").arg(search_track->event.at(i)->params.at(j)));
                }
            }
        } else i++;
    }

    return result;
}

QString MidiFile::getTrackEvent(int tracknum, int eventnum) {
    int i = 0;  QString result;

    Event *search_event = track.at(tracknum)->event.at(eventnum);

    result.append(QString("%1").arg(search_event->event));
    while(i < search_event->params.count()) {
        result.append(QString("%1").arg(search_event->params.at(i++)));
    }

    return result;
}

int MidiFile::numTracks() {
    return track.count();
}

int MidiFile::numEvents(int tracknum) {
    return track.at(tracknum)->event.count();
}
