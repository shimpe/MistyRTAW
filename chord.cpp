#include "chord.h"
#include "interval.h"
#include <QSet>

Chord::Chord(const QList<QString> &TheoryNotes, const QString &RootNote, unsigned int Inversion)
: m_TheoryNotes(TheoryNotes)
, m_RootNote(RootNote)
, m_Inversion(Inversion)
{
    if (RootNote == QString(""))
    {
        m_RootNote = TheoryNotes[0];
    }
}

QList<QString> Chord::TransposeTo(const QString &NewNote) const
{
    QList<QString> Result;
    Result << NewNote;
    for (QList<QString>::const_iterator it = m_TheoryNotes.begin()+1; it != m_TheoryNotes.end(); ++it)
    {
        Result << (Interval(m_TheoryNotes[0], *it).TransposeTo(NewNote)[1]);
    }
    return Result;
}

QList<int> Chord::ToIntervalPattern() const
{
  // example ['c','e','g'] to interval pattern: [4,3]
  // because between c and e are 4 semitones,
  // and between e and g are 3 semitones
  if (m_TheoryNotes.size() == 0)
      return QList<int>();
  else if (m_TheoryNotes.size() == 1)
      return QList<int>() << 0;
  else
  {
      int Index = 0;
      QList<int> Result;
      while ((Index+1) < m_TheoryNotes.size())
      {
          Result << Interval(m_TheoryNotes[Index], m_TheoryNotes[Index+1]).GetNoOfSemitones();
          Index++;
      }
      return Result;
  }
}



QList<QString> Chord::WithoutDuplicateNotes() const
{
    // example: ['a','c','e','a','c'] without duplicate notes => ['a','c','e']
    // keep the ordering intact
    QSet<QString> AlreadyEncounteredNotes;
    QList<QString> NewListOfNotes;
    for (QList<QString>::const_iterator it = m_TheoryNotes.begin(); it != m_TheoryNotes.end(); ++it)
    {
        if (!AlreadyEncounteredNotes.contains(*it))
        {
            NewListOfNotes << *it;
            AlreadyEncounteredNotes << *it;
        }
    }
    return NewListOfNotes;
}



QList<QString> Chord::SortedRelativeToFirstNote() const
{
    // Example: sorting ['e','c','g','e'] relative to first note => ['e','g','c']
    if (m_TheoryNotes.size() < 3)
        return m_TheoryNotes; // already sorted

    // step 1: sort alphabetically; this allows to use inversions instead of permutations
    //         avoiding combinatorial explosion
    QList<QString> CopyNotes = m_TheoryNotes;
    qSort(CopyNotes.begin(), CopyNotes.end());

    // step 2: sort musically
    qSort(CopyNotes.begin(), CopyNotes.end(), Chord::MusicSort);

    // step 3: make sure original first note appears first
    int IndexFirst = CopyNotes.indexOf(m_TheoryNotes[0]);
    QList<QString> ResultPart1 = CopyNotes.mid(IndexFirst,-1);
    QList<QString> ResultPart2 = CopyNotes.mid(0, IndexFirst);
    ResultPart1.append(ResultPart2);
    return ResultPart1;
}


QList<QList<QString> > Chord::CreateAllInversions() const
{
    QList<QList<QString> > Result;
    for (int Index=0; Index < m_TheoryNotes.size(); ++Index)
    {
        QList<QString> PartialResult = m_TheoryNotes.mid(Index,-1);
        QList<QString> PartialResult2= m_TheoryNotes.mid(0, Index);
        PartialResult.append(PartialResult2);
        Result << PartialResult;
    }

    return Result;
}


QList<QString> Chord::Simplify() const
{
    // the simplified chord is the chord with all notes rearranged so that they are spaced as closely as possible
    // e.g. ['a','e','c'] simplified => ['a','c','e']
    QList<QString> SimplerChord = WithoutDuplicateNotes();
    SimplerChord = Chord(SimplerChord).SortedRelativeToFirstNote();
    QList<QList<QString> > Inversions = Chord(SimplerChord).CreateAllInversions();
    QHash< QString, QList<QString> > MinimumEnergyChordList; // map from interval pattern to list of theorynote
    QList< QList<int> > PatList;
    int Minimum = -1;
    for (QList<QList<QString> >::const_iterator it = Inversions.begin(); it != Inversions.end(); ++it)
    {
        QList<int> Pat = Chord(*it).ToIntervalPattern();
        int sum=0;
        QListIterator<int> i(Pat);
        while (i.hasNext())
            sum += i.next();
        if (sum < Minimum || Minimum == -1)
        {
            Minimum = sum;
            MinimumEnergyChordList[PatternToKey(Pat)] = *it;
            PatList << Pat;
        }
        else if (sum == Minimum)
        {
            MinimumEnergyChordList[PatternToKey(Pat)] = *it;
            PatList << Pat;
        }
    }
    QList<QList<int> > SortedPatList = PatList;
    qSort(SortedPatList.begin(), SortedPatList.end(), PatternSort);
    return MinimumEnergyChordList[PatternToKey(SortedPatList[0])];
}

bool Chord::MusicSort(const QString &note1, const QString &note2)
{
    int d1 = Interval(note1,note2).GetNoOfSemitones();
    int d2 = Interval(note2,note1).GetNoOfSemitones();
    return (d1 < d2);
}

bool Chord::PatternSort(const QList<int> &list1, const QList<int> &list2)
{
    // one list shorter than the other? sort based on length
    if (list1.length() < list2.length())
        return true;
    if (list1.length() > list2.length())
        return false;

    // both lists have same number of elements: perform lexicographic sorting
    QList<int>::const_iterator it1 = list1.begin();
    QList<int>::const_iterator it2 = list2.begin();
    for (;it1 != list1.end();++it1,++it2)
    {
        if (*it1 < *it2)
            return true;
        if (*it1 > *it2)
            return false;
        return PatternSort(list1.mid(1), list2.mid(1));
    }
    return false;
}

QString Chord::PatternToKey(const QList<int> &Pattern)
{
    QString Key = "";
    for (QList<int>::const_iterator it = Pattern.begin(); it != Pattern.end(); ++it)
    {
        Key += QString(*it);
    }
    return Key;
}

bool Chord::operator ==(const Chord &Other) const
{
    return m_TheoryNotes == Other.m_TheoryNotes && m_RootNote == Other.m_RootNote && m_Inversion == Other.m_Inversion;
}

/*
---
TESTSUITE : Chord
TYPE   : COLUMNBASED
LINK : [ chord.cpp, interval.cpp ]
INCLUDE: [ chord.h, <QString>, <QHash>, <QList> ]
INCLUDEDIR : [ /usr/include/qt4,/usr/include/qt4/QtCore ]
BINLIB : [QtCore]
STUBS  :
PRE    : |
    QList<QString> Notes;
    QList<QString> Notes2;
    QList<int> List;
POST   :
CODE   : [
  [
   [ 'Simplify',   'Notes << $1',         'Notes2 << $1' , ~, 'EXPECT_EQ(Chord(Notes).Simplify(), Notes2)'],
   [ 'nochange',   '"a",,"c",,"e"',       '"a",,"c",,"e"', ~, '.'                                                ],
   [ 'ordering',   '"a",,"e",,"c"',       '"a",,"c",,"e"', ~, '.'                                                ],
   [ 'duplicates', '"a",,"c",,"e",,"a"',  '"a",,"c",,"e"', ~, '.'                                                ],
   [ 'inversion',  '"e",,"a",,"c",,"e"',  '"a",,"c",,"e"', ~, '.'                                                ],
  ],
  [
   [ 'TransposeTo',   'Notes << $1',      'Notes2 << $1' ,     ~, 'EXPECT_EQ(Chord(Notes).TransposeTo($1), Notes2)'],
   [ 'nochange',      '"e",,"g#",,"b"',     '"e",,"g#",,"b"',  ~, '"e"'                                                   ],
   [ 'semitone',      '"e",,"g#",,"b"',     '"f",,"a",,"c"',   ~, '"f"'                                                   ],
   [ 'semitone2',     '"e",,"b",,"g#"',     '"f",,"c",,"a"',   ~, '"f"'                                                   ],
   [ 'exotic',        '"c",,"e",,"g"',      '"e#",,"gx",,"b#"',~, '"e#"'                                                  ],
  ],
  [
   [ 'ToIntervalPattern', 'Notes << $1',  'List << $1',      ~, 'EXPECT_EQ(Chord(Notes).ToIntervalPattern(), List)'],
   [ 'simple',            '"c",,"e",,"g"',"4,,3",            ~, '.'                                                ],
  ],
]
*/
