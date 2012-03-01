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

#include "chorddescriptor.h"

ChordDescriptor::ChordDescriptor()
: m_BaseName("PROGRAMMING ERROR")
, m_Modifier("PROGRAMMING ERROR")
, m_Slash("PROGRAMMING ERROR")
{}

ChordDescriptor::ChordDescriptor(const QString &BaseName, const QString &Modifier, const QString &Slash)
: m_BaseName(BaseName)
, m_Modifier(Modifier)
, m_Slash(Slash)
{}

const QString &ChordDescriptor::GetBaseName() const
{
    return m_BaseName;
}

const QString & ChordDescriptor::GetModifier() const
{
    return m_Modifier;
}

const QString & ChordDescriptor::GetSlash() const
{
    return m_Slash;
}

bool ChordDescriptor::operator==(const ChordDescriptor &Other) const
{
    return m_BaseName == Other.m_BaseName && m_Modifier == Other.m_Modifier && m_Slash == Other.m_Slash;
}
