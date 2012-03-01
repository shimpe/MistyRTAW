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

#ifndef INTERVAL_H
#define INTERVAL_H

#include <QString>
#include <QList>
#include <QHash>

class Interval
{
public:
    Interval(const QString &TheoryNote1, const QString &TheoryNote2);

    QString GetFirstNote() const;
    QString GetSecondNote() const;

    unsigned int GetNoteNameDistance() const;
    unsigned int GetNoOfSemitones() const;

    QList<QString> TransposeTo(const QString &NewNote) const;
    QList<int> ToIntervalPattern() const;

private:
    QString m_TheoryNote1;
    QString m_TheoryNote2;

    QList<QString> m_DiatonicScaleNotes;
    QList<QList<QString> > m_ChromaticScaleNotes;
    QHash<QString, int> m_ChromaticNoteToIndex;
    QHash<int, QString> m_Modifiers;
};

#endif // INTERVAL_H
