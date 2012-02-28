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

private:
    QList<QString> WithoutDuplicateNotes() const;
    QList<QString> SortedRelativeToFirstNote() const;

    static bool MusicSort(const QString &note1, const QString &note2);
    static bool PatternSort(const QList<int> &list1, const QList<int> &list2);

private:
    QList<QString> m_TheoryNotes;
    QString m_RootNote;
    unsigned int m_Inversion;
};

#endif // CHORD_H
