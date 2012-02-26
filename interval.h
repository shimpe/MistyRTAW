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

    Interval TransposeTo(const QString &NewNote) const;
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
