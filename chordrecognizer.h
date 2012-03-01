/*
 This file is part of MistyRTAW.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/


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
