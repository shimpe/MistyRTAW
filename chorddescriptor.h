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
