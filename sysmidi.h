#ifndef SYSMIDI_H
#define SYSMIDI_H

#include "RtMidi.h"
#include "RtError.h"
#include <string>

class SysMIDI {
    public:
        SysMIDI();
        int openvirtual(std::string ConnectionName);

    private:
        RTMidiIn *in;
};

#endif // SYSMIDI_H
