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
