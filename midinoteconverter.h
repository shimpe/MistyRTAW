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
