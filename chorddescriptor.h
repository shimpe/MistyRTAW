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

#ifndef CHORDDESCRIPTOR_H
#define CHORDDESCRIPTOR_H

#include <QString>

class ChordDescriptor
{
public:
    ChordDescriptor();
    ChordDescriptor(const QString &BaseName, const QString &Modifier, const QString &Slash);
    bool operator==(const ChordDescriptor &Other) const;

    const QString &GetBaseName() const;
    const QString &GetModifier() const;
    const QString &GetSlash() const;

private:
    QString m_BaseName;
    QString m_Modifier;
    QString m_Slash;
};

#endif // CHORDDESCRIPTOR_H
