// The MidiData files hold the enums & classes common to both the Midi & MidiFile classes.

#include "mididata.h"

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
