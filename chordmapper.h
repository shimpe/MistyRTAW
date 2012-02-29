#ifndef CHORDMAPPER_H
#define CHORDMAPPER_H

#include "chorddescriptor.h"
#include <QHash>

class ChordMapper
{
public:
    ChordMapper();

    ChordDescriptor Lookup(const ChordDescriptor &Chord) const;

private:
    QHash<QString, QPair<QString,QString> > m_Map;
};

#endif // CHORDMAPPER_H
