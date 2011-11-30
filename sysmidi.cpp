#include "sysmidi.h"

SysMIDI::SysMIDI(std::string ConnectionName) {
    RtError error;

    try {
        in = new RTMidiIn();
    } catch (&error) {
        error.printMessage();
    }
}

