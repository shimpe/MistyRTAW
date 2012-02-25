#ifndef MIDINOTECONVERTER_H
#define MIDINOTECONVERTER_H

#include "mididata.h"
#include <QHash>
#include <QString>

class MidiNoteConverter
{
public:
    MidiNoteConverter();

    QString midiNoteToString(const notes &Note) const;
    QString midiNoteToTheoryNote(const notes &Note) const;

private:
    QHash<notes, QString> m_MidiNoteToString;
    QHash<notes, QString> m_MidiNoteToTheoryNote;
};

#endif // MIDINOTECONVERTER_H
