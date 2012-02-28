#ifndef CHORDRECOGNIZER_H
#define CHORDRECOGNIZER_H

#include <QHash>
#include <QString>
#include <QPair>
#include <QList>
#include "chorddescriptor.h"

class ChordRecognizer
{
public:
    ChordRecognizer();
    ChordDescriptor RecognizeChord(const QList<QString> &TheoryNotes, bool &ChordRecognized) const;

private:
    void RegisterNewChordType(const QList<QString> &TheoryNotes, const ChordDescriptor &ChordDescr);

private:
    QHash<QString, QPair<ChordDescriptor, unsigned int> > m_PatternToDescriptor;
};

#endif // CHORDRECOGNIZER_H
