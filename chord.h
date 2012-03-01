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

#ifndef CHORD_H
#define CHORD_H

#include <QString>
#include <QList>

class Chord
{
public:
    Chord(const QList<QString> &TheoryNotes, const QString &RootNote="", unsigned int Inversion=0);
    QList<QString> TransposeTo(const QString &NewNote) const;
    QList<int> ToIntervalPattern() const;
    QList<QString> Simplify() const;
    bool operator==(const Chord &Other) const;
    static QString PatternToKey(const QList<int> &Pattern);
    QList<QList<QString> > CreateAllInversions() const;
    QList<QString> WithoutDuplicateNotes() const;

private:
    QList<QString> SortedRelativeToFirstNote() const;

    static bool MusicSort(const QString &note1, const QString &note2);
    static bool PatternSort(const QList<int> &list1, const QList<int> &list2);

private:
    QList<QString> m_TheoryNotes;
    QString m_RootNote;
    unsigned int m_Inversion;
};

#endif // CHORD_H
