#ifndef TESTMIDIOUTPUT_H
#define TESTMIDIOUTPUT_H

#include <QThread>
#include <QList>
#include "midifile.h"

class TestMidiOutput : public QThread
{
    Q_OBJECT
public:
    explicit TestMidiOutput(QList<Port *> output_ports, MidiFile *mf);
    void run();
    void stop();
    
signals:
    void addEvent(Event *e);
    void send_message(QString message);
public slots:

private:
    MidiFile *midi;
    QList<Port *>ports;
    bool running;
};

#endif // TESTMIDIOUTPUT_H
