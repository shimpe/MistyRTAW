#include "interval.h"

Interval::Interval(const QString &TheoryNote1, const QString &TheoryNote2)
:m_TheoryNote1(TheoryNote1)
,m_TheoryNote2(TheoryNote2)
{
    // possible note names
    m_DiatonicScaleNotes << "a" << "b" << "c" << "d" << "e" << "f" << "g";

    // having support for enharmonic equivalent notes will help during music theory operations
    // when going back to midi, we can normalize everything back to sharps
    m_ChromaticScaleNotes << (QList<QString>() << "c" << "b#" << "dbb")
                          << (QList<QString>() << "c#" << "bx" << "db")
                          << (QList<QString>() << "d" << "cx" << "ebb")
                          << (QList<QString>() << "d#" << "eb" << "fbb")
                          << (QList<QString>() << "e" << "dx" << "fb")
                          << (QList<QString>() << "f" << "e#" << "gbb")
                          << (QList<QString>() << "f#" << "ex" << "gb")
                          << (QList<QString>() << "g" << "fx" << "abb")
                          << (QList<QString>() << "g#" << "ab" )
                          << (QList<QString>() << "a" << "gx" << "bbb")
                          << (QList<QString>() << "a#" << "bb" << "cbb")
                          << (QList<QString>() << "b" << "ax" << "cb");
    unsigned int Index = 0;
    for (QList<QList<QString> >::const_iterator it = m_ChromaticScaleNotes.begin();
         it != m_ChromaticScaleNotes.end();
         ++it,++Index)
    {
        for (QList<QString>::const_iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
        {
            m_ChromaticNoteToIndex[*it2] = Index;
        }
    }

    // modifiers required during transposition
    m_Modifiers[-12] = "";
    m_Modifiers[-11] = "#";
    m_Modifiers[-10] = "x";
    m_Modifiers[-2] = "bb";
    m_Modifiers[-1] = "b";
    m_Modifiers[0] = "";
    m_Modifiers[1] = "#";
    m_Modifiers[2] = "x";
}

QString Interval::GetFirstNote() const
{
    return m_TheoryNote1;
}

QString Interval::GetSecondNote() const
{
    return m_TheoryNote2;
}

unsigned int Interval::GetNoteNameDistance() const
{
    unsigned int FirstNoteIndex = m_DiatonicScaleNotes.indexOf(QString(m_TheoryNote1[0]));
    unsigned int SecondNoteIndex= m_DiatonicScaleNotes.indexOf(QString(m_TheoryNote2[0]));
    if (FirstNoteIndex > SecondNoteIndex)
        return SecondNoteIndex+7-FirstNoteIndex;
    else
        return SecondNoteIndex-FirstNoteIndex;
}

unsigned int Interval::GetNoOfSemitones() const
{
    unsigned int FirstNoteIndex = m_ChromaticNoteToIndex[m_TheoryNote1];
    unsigned int SecondNoteIndex = m_ChromaticNoteToIndex[m_TheoryNote2];
    int Difference = SecondNoteIndex - FirstNoteIndex;
    if (Difference < 0)
        return Difference + 12;
    else
        return Difference;
}

Interval Interval::TransposeTo(const QString &NewTheoryNote) const
{
    int NewNoteIndex = m_DiatonicScaleNotes.indexOf(QString(m_TheoryNote2[0])) +
            Interval(m_TheoryNote1, NewTheoryNote).GetNoteNameDistance();
    if (NewNoteIndex > 6)
        NewNoteIndex -= 7;
    QString SecondNote = m_DiatonicScaleNotes[NewNoteIndex];
    int ModifierKey = Interval(m_TheoryNote1, m_TheoryNote2).GetNoOfSemitones()
            - Interval(m_TheoryNote1, m_TheoryNote2).GetNoOfSemitones();
    return Interval(NewTheoryNote, SecondNote + m_Modifiers[ModifierKey]);
}

QList<int> Interval::ToIntervalPattern() const
{
    return QList<int>() << GetNoteNameDistance() << GetNoOfSemitones();
}

/*
---
TESTSUITE : Intervals
TYPE   : COLUMNBASED
LINK : [ interval.cpp ]
INCLUDE: [ interval.h, <QString>, <QHash>, <QList> ]
INCLUDEDIR : [ /usr/include/qt4,/usr/include/qt4/QtCore ]
BINLIB : [QtCore]
STUBS  :
PRE    : |
    typedef Interval I;
POST   :
CODE   : [
  [
   [ 'distances',  ~, 'EXPECT_EQ(I("$1","$2").GetNoteNameDistance(), $3)', 'EXPECT_EQ(I("$1","$2").GetNoOfSemitones(), $3)'],
   [ 'zero',       ~, 'a,a,0'                                            , 'a,a,0'       ],
   [ 'one_1',      ~, 'a,b,1'                                            , 'a,b,2'       ],
   [ 'one_2',      ~, 'a#,bb,1'                                          , 'a#,bb,0'     ],
   [ 'wrapping',   ~, 'gb,a,1'                                           , 'gb,a,3'      ],
   [ 'inverted',   ~, 'a,g#,6'                                           , 'a,g,10'      ],
   [ 'doublesharp',~, 'ax,bbb,1'                                         , 'ax,bbb,10'   ],
   [ 'doubleshrp2',~, 'bbb,ax,6'                                         , 'bbb,ax,2'    ],
  ],
  [
   [ 'distances2', ~, 'EXPECT_EQ(I("$1","$2").ToIntervalPattern(), (QList<int>() << $3 << $4))'],
   [ 'zero',       ~, 'a,a,0,0'    ],
   [ 'one_1',      ~, 'a,b,1,2'    ],
   [ 'one_2',      ~, 'a#,bb,1,0'  ],
   [ 'wrapping',   ~, 'gb,a,1,3'   ],
   [ 'inverted',   ~, 'a,g#,6,11'  ],
   [ 'doublesharp',~, 'ax,bbb,1,10'],
   [ 'doubleshrp2',~, 'bbb,ax,6,2' ],
  ]
]
*/
