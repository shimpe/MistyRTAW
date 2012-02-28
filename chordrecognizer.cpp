#include "chordrecognizer.h"
#include "chord.h"
#include <QDebug>

ChordRecognizer::ChordRecognizer()
{
    // behold the power of teach by example ...
    // each line teaches the system tens of new chords

    // note that since midi doesn't distinguish between
    // e.g gb and f# there's no point in maintaining a distinction
    // between (say) an augmented fourth and a dimished fifth

    // let's make this thing recognize intervals ("2-note chords")
    // recognize minor second
    QList<QString> MinorSecond = QList<QString>() << "c" << "c#";
    RegisterNewChordType(MinorSecond,ChordDescriptor("c","minorsecond","c"));

    // recognize major second
    QList<QString> MajorSecond = QList<QString>() << "c" << "d";
    RegisterNewChordType(MajorSecond,ChordDescriptor("c","majorsecond","c"));

    // recognize minor third
    QList<QString> MinorThird = QList<QString>() << "c" << "eb";
    RegisterNewChordType(MinorThird,ChordDescriptor("c","minorthird","c"));

    // recognize major third
    QList<QString> MajorThird = QList<QString>() << "c" << "e";
    RegisterNewChordType(MajorThird,ChordDescriptor("c","majorthird","c"));

    // recognize perfect fourth == inverse of perfect fifth
    // QList<QString> PerfectFourth = QList<QString>() << "c" << "f";
    // RegisterNewChordType(PerfectFourth,ChordDescriptor("c","majorfourth","c"));

    // recognize augmented fourth (also known as tritone, or "diabolicus in musica" *shiver*)
    QList<QString> AugmentedFourth = QList<QString>() << "c" << "f#";
    RegisterNewChordType(AugmentedFourth,ChordDescriptor("c","augmentedfourth","c"));

    // perfect fifth (also known as PowerChord)
    QList<QString> PowerChord = QList<QString>() << "c" << "g";
    RegisterNewChordType(PowerChord,ChordDescriptor("c","perfectfifth","c"));

    // minor sixth == inverse of major third
    // QList<QString> MinorSixthInt = QList<QString>() << "c" << "ab";
    // RegisterNewChordType(MinorSixthInt,ChordDescriptor("c","minorsixth","c"));

    // major sixth == inverse of minor third
    // QList<QString> MajorSixth = QList<QString>() << "c" << "a";
    // RegisterNewChordType(MajorSixth,ChordDescriptor("c","majorsixth","c"));

    // minor seventh == inverse of major second
    // QList<QString> MinorSeventh = QList<QString>() << "c" << "bb";
    // RegisterNewChordType(MinorSeventh,ChordDescriptor("c","minorseventh","c"));

    // major seventh == inverse of minor second
    // QList<QString> MajorSeventh = QList<QString>() << "c" << "b";
    // RegisterNewChordType(MajorSeventh,ChordDescriptor("c","majorseventh","c"));

    // let's make this thing also recognize chords with three and more notes

    // recognize all major chords in all keys and inversions
    QList<QString> MajorChord = QList<QString>() << "c" << "e" << "g";
    RegisterNewChordType(MajorChord,ChordDescriptor("c","","c"));

    // recognize all minor chords in all keys and inversions
    QList<QString> MinorChord = QList<QString>() << "c" << "eb" << "g";
    RegisterNewChordType(MinorChord,ChordDescriptor("c","m","c"));

    // recognize all augmented triads in all keys and inversions
    QList<QString> AugmentedTriad = QList<QString>() << "c" << "e" << "g#";
    RegisterNewChordType(AugmentedTriad,ChordDescriptor("c","aug","c"));

    // recognize all diminished triads in all keys and inversions
    QList<QString> DiminishedTriad = QList<QString>() << "c" << "e" << "gb";
    RegisterNewChordType(DiminishedTriad,ChordDescriptor("c","dim5","c"));

    // recognize all suspended second triads in all keys and inversions == inversion of sus4
    // QList<QString> Sus2 = QList<QString>() << "c" << "d" << "g";
    // RegisterNewChordType(Sus2,ChordDescriptor("c","sus2","c"));

    // recognize all suspended fourth triads in all keys and inversions
    QList<QString> Sus4 = QList<QString>() << "c" << "f" << "g";
    RegisterNewChordType(Sus4,ChordDescriptor("c","sus4","c"));

    // recognize all seventh omit5 chords
    QList<QString> SevenOmit5 = QList<QString>() << "c" << "e" << "bb";
    RegisterNewChordType(SevenOmit5,ChordDescriptor("c","7(omit5)","c"));

    // recognize all seventh omit3 chords
    QList<QString> SevenOmit3 = QList<QString>() << "c" << "g" << "bb";
    RegisterNewChordType(SevenOmit3,ChordDescriptor("c","7(omit3)","c"));

    // recognize all major seventh omit5 chords
    QList<QString> MajSevenOmit5 = QList<QString>() << "c" << "e" << "b";
    RegisterNewChordType(MajSevenOmit5,ChordDescriptor("c","Maj7(omit5)","c"));

    // recognize all major seventh omit3 chords
    QList<QString> MajSevenOmit3 = QList<QString>() << "c" << "g" << "b";
    RegisterNewChordType(MajSevenOmit3,ChordDescriptor("c","Maj7(omit3)","c"));

    // recognize all minor seventh omit5 chords
    QList<QString> Minor7omit5 = QList<QString>() << "c" << "eb" << "bb";
    RegisterNewChordType(Minor7omit5,ChordDescriptor("c","m7(omit5)","c"));

    // recognize all minor seventh omit3 chords == inverse of 7(omit3)
    // QList<QString> Minor7omit3 = QList<QString>() << "c" << "g" << "bb";
    // RegisterNewChordType(Minor7omit3,ChordDescriptor("c","m7(omit3)","c"));

    // recognize all added fourth chords
    QList<QString> Add4 = QList<QString>() << "c" << "e" << "f" << "g";
    RegisterNewChordType(Add4,ChordDescriptor("c","add4","c"));

    // recognize all sixth chords == inverse of m7
    // QList<QString> Sixth = QList<QString>() << "c" << "e" << "g" << "a";
    // RegisterNewChordType(Sixth,ChordDescriptor("c","6","c"));

    // recognize all minor sixth chords == inverse of m7(b5)
    // QList<QString> MinorSixth = QList<QString>() << "c" << "eb" << "g" << "a";
    // RegisterNewChordType(MinorSixth,ChordDescriptor("c","m6","c"));

    // recognize all six/seven chords
    QList<QString> SixSeven = QList<QString>() << "c" << "e" << "g" << "a" << "bb";
    RegisterNewChordType(SixSeven,ChordDescriptor("c","6/7","c"));

    // recognize all minor six/seven chords
    QList<QString> MinorSixSeven = QList<QString>() << "c" << "eb" << "g" << "a" << "bb";
    RegisterNewChordType(MinorSixSeven,ChordDescriptor("c","m6/7","c"));

    // recognize all six/seven suspended chords
    QList<QString> SusSixSeven = QList<QString>() << "c" << "f#" << "g" << "a" << "bb";
    RegisterNewChordType(SusSixSeven,ChordDescriptor("c","6/7sus","c"));

    // recognize all minor added 9 chords
    QList<QString> SixSevenAdd9 = QList<QString>() << "c" << "eb" << "g" << "d";
    RegisterNewChordType(SixSevenAdd9,ChordDescriptor("c","m(9)","c"));

    // recognize all seventh chords
    QList<QString> Seven = QList<QString>() << "c" << "e" << "g" << "bb";
    RegisterNewChordType(Seven,ChordDescriptor("c","7","c"));

    // recognize all major 7th chords
    QList<QString> MajorSeven = QList<QString>() << "c" << "e" << "g" << "b";
    RegisterNewChordType(MajorSeven,ChordDescriptor("c","Maj7","c"));

    // recognize all minor 7th chords
    QList<QString> MinorSeven = QList<QString>() << "c" << "eb" << "g" << "bb";
    RegisterNewChordType(MinorSeven,ChordDescriptor("c","m7","c"));

    // recognize all seven sus4 chords
    QList<QString> MinorSevenSus4 = QList<QString>() << "c" << "f" << "g" << "bb";
    RegisterNewChordType(MinorSevenSus4,ChordDescriptor("c","7sus4","c"));

    // recognize all seven aug5 chords
    QList<QString> SevenAug5 = QList<QString>() << "c" << "e" << "g#" << "bb";
    RegisterNewChordType(SevenAug5,ChordDescriptor("c","7(#5)","c"));

    // recognize all minor seven aug5 chords
    QList<QString> MajSevenAug5 = QList<QString>() << "c" << "e" << "g#" << "b";
    RegisterNewChordType(MajSevenAug5,ChordDescriptor("c","Maj7(#5)","c"));

    // recognize all maj 7 dim 5 chords
    QList<QString> MajSevenDim5 = QList<QString>() << "c" << "e" << "gb" << "b";
    RegisterNewChordType(MajSevenDim5,ChordDescriptor("c","Maj7(b5)","c"));

    // recognize all seven dim5 chords
    QList<QString> SevenDim5 = QList<QString>() << "c" << "e" << "gb" << "bb";
    RegisterNewChordType(SevenDim5,ChordDescriptor("c","7(b5)","c"));

    // recognize all diminished 7 chords
    QList<QString> DimSeven = QList<QString>() << "c" << "eb" << "gb" << "a";
    RegisterNewChordType(DimSeven,ChordDescriptor("c","dim7","c"));

    // recognize all half-diminished 7 chords
    QList<QString> HalfDimSeven = QList<QString>() << "c" << "eb" << "gb" << "bb";
    RegisterNewChordType(HalfDimSeven,ChordDescriptor("c","m7(b5)","c"));

    // recognize all minor/major 7 chords
    QList<QString> MinMajSeven = QList<QString>() << "c" << "eb" << "g" << "b";
    RegisterNewChordType(MinMajSeven,ChordDescriptor("c","mMaj7","c"));

    // recognize all sixth added 9 chords
    QList<QString> SixAddNine = QList<QString>() << "c" << "d" << "e" << "a";
    RegisterNewChordType(SixAddNine,ChordDescriptor("c","6(9)","c"));

    // recognize all minor sixth/nine chords
    QList<QString> MinorSixAddNine = QList<QString>() << "c" << "eb" << "g" << "a" << "d";
    RegisterNewChordType(MinorSixAddNine,ChordDescriptor("c","m6(9)","c"));

    // recognize all minor sixth/nine omit 5 chords
    QList<QString> MinorSixAddNine2 = QList<QString>() << "c" << "eb" << "a" << "d";
    RegisterNewChordType(MinorSixAddNine2,ChordDescriptor("c","m6(omit5)(9)","c"));

    // recognize all seventh added ninth chords
    QList<QString> SevenAddNine = QList<QString>() << "c" << "d" << "e" << "bb";
    RegisterNewChordType(SevenAddNine,ChordDescriptor("c","7(9)","c"));

    // recognize all seventh augmented ninth chords
    QList<QString> SevenAugNine = QList<QString>() << "c" << "e" << "g" << "bb" << "d#";
    RegisterNewChordType(SevenAugNine,ChordDescriptor("c","7(#9)","c"));

    // recognize all seventh diminished ninth chords
    QList<QString> SevenDimNine = QList<QString>() << "c" << "c#" << "e" << "bb";
    RegisterNewChordType(SevenDimNine,ChordDescriptor("c","7(b9)","c"));

    // recognize all seventh aug11 chords == inversion of 7(b5)
    // QList<QString> SevenAug11 = QList<QString>() << "c" << "e" << "f#" << "bb";
    // RegisterNewChordType(SevenAug11,ChordDescriptor("c","7(#11)","c"));

    // recognize all major seventh added ninth chords
    QList<QString> MajSevenAddNine = QList<QString>() << "c" << "d" << "e" << "b";
    RegisterNewChordType(MajSevenAddNine,ChordDescriptor("c","Maj7(9)","c"));

    // recognize all major seventh added thirteen chords
    QList<QString> MajSevenAdd13 = QList<QString>() << "c" << "e" << "g" << "a" << "b";
    RegisterNewChordType(MajSevenAdd13,ChordDescriptor("c","Maj7(13)","c"));

    // recognize all major seventh augm 11th chords == inversion of Maj7(b5)
    // QList<QString> MajSevenAug11 = QList<QString>() << "c" << "e" << "f#" << "b";
    // RegisterNewChordType(MajSevenAug11,ChordDescriptor("c","Maj7(#11)","c"));

    // recognize all minor seven added 9 chords
    QList<QString> MinSevenAdd9 = QList<QString>() << "c" << "d" << "eb" << "bb";
    RegisterNewChordType(MinSevenAdd9,ChordDescriptor("c","m7(9)","c"));

    // recognize all minor/Major 7 added 9 chords
    QList<QString> MinMajSevenAdd9 = QList<QString>() << "c" << "d" << "eb" << "b";
    RegisterNewChordType(MinMajSevenAdd9,ChordDescriptor("c","mMaj7(9)","c"));

    // recognize all seven added 13 chords
    QList<QString> SevenAdd13 = QList<QString>() << "c" << "e" << "a" << "bb";
    RegisterNewChordType(SevenAdd13,ChordDescriptor("c","7(13)","c"));

    // recognize all seven diminished 13 chords == inversion of 7(#5)
    // QList<QString> SevenDim13 = QList<QString>() << "c" << "e" << "g#" << "bb";
    // RegisterNewChordType(SevenDim13,ChordDescriptor("c","7(b13)","c"));

    // recognize all 6/9 chords
    QList<QString> SixSlashNine = QList<QString>() << "c" << "e" << "g" << "a" << "d";
    RegisterNewChordType(SixSlashNine,ChordDescriptor("c","6/9","c"));

    // recognize all major 9th chords
    QList<QString> MajNine = QList<QString>() << "c" << "e" << "g" << "b" << "d";
    RegisterNewChordType(MajNine,ChordDescriptor("c","Maj9","c"));

    // recognize all 9 chords
    QList<QString> Nine = QList<QString>() << "c" << "e" << "g" << "bb" << "d";
    RegisterNewChordType(Nine,ChordDescriptor("c","9","c"));

    // recognize all minor 9 chords
    QList<QString> MinorNine = QList<QString>() << "c" << "eb" << "g" << "bb" << "d";
    RegisterNewChordType(MinorNine,ChordDescriptor("c","m9","c"));

    // recognize 9 aug5 chords
    QList<QString> NineAug5 = QList<QString>() << "c" << "e" << "g#" << "bb" << "d";
    RegisterNewChordType(NineAug5,ChordDescriptor("c","9(#5)","c"));

    // recognize 9 dim5 chords == inversion of 9(#5)
    // QList<QString> NineDim5 = QList<QString>() << "c" << "e" << "gb" << "bb" << "d";
    // RegisterNewChordType(NineDim5,ChordDescriptor("c","9(b5)","c"));

    // minor ninth dim5 chords
    QList<QString> MinorNineDim5 = QList<QString>() << "c" << "eb" << "gb" << "bb" << "d";
    RegisterNewChordType(MinorNineDim5,ChordDescriptor("c","m9(b5)","c"));

    // minor ninth aug5 chords
    QList<QString> MinorNineAug5 = QList<QString>() << "c" << "eb" << "g#" << "bb" << "d";
    RegisterNewChordType(MinorNineAug5,ChordDescriptor("c","m9(#5)","c"));

    // 11th chords
    QList<QString> Eleven = QList<QString>() << "c" << "e" << "g" << "bb" << "d" << "f";
    RegisterNewChordType(Eleven,ChordDescriptor("c","11","c"));

    // maj 11th chords
    QList<QString> Maj11 = QList<QString>() << "c" << "e" << "g" << "b" << "d" << "f";
    RegisterNewChordType(Maj11,ChordDescriptor("c","Maj11","c"));

    // min 11th chords
    QList<QString> Minor11 = QList<QString>() << "c" << "eb" << "g" << "bb" << "d" << "f";
    RegisterNewChordType(Minor11,ChordDescriptor("c","m11","c"));

    // min 11th dim5 chords
    QList<QString> Minor11Dim5 = QList<QString>() << "c" << "eb" << "gb" << "bb" << "d" << "f";
    RegisterNewChordType(Minor11Dim5,ChordDescriptor("c","m11(b5)","c"));

    // min 11th aug5 chords == inversion of m11
    //QList<QString> Minor11Aug5 = QList<QString>() << "c" << "eb" << "g#" << "bb" << "d" << "f";
    //RegisterNewChordType(Minor11Aug5,ChordDescriptor("c","m11(#5)","c"));

    // 13th chords
    QList<QString> Thirteen = QList<QString>() << "c" << "e" << "g" << "bb" << "d" << "a";
    RegisterNewChordType(Thirteen,ChordDescriptor("c","13","c"));
    QList<QString> Thirteen2 = QList<QString>() << "c" << "e" << "g" << "bb" << "d" << "f" << "a";
    RegisterNewChordType(Thirteen2,ChordDescriptor("c","13","c"));

    // maj 13th chord
    QList<QString> Maj13 = QList<QString>() << "c" << "e" << "g" << "b" << "d" << "a";
    RegisterNewChordType(Maj13,ChordDescriptor("c","Maj13","c"));

    // min 13 added 11 chord == inversion of 6/9 chord
    // QList<QString> Maj13Add11 = QList<QString>() << "c" << "eb" << "g" << "bb" << "f";
    // RegisterNewChordType(Maj13Add11,ChordDescriptor("c","m7(11)","c"));

    // minor 7th add13 == inversion of m6/7 chord
    // QList<QString> Min7Add13 = QList<QString>() << "c" << "eb" << "g" << "a" << "bb";
    // RegisterNewChordType(Min7Add13,ChordDescriptor("c","m7(13)","c"));

    // min 13th == inversion of 13 chord
    // QList<QString> Min13 = QList<QString>() << "c" << "eb" << "g" << "bb" << "d" << "f" << "a";
    // RegisterNewChordType(Min13,ChordDescriptor("c","m13","c"));

    // minor 9/major 7
    QList<QString> Min9Maj7 = QList<QString>() << "c" << "eb" << "g" << "b" << "d";
    RegisterNewChordType(Min9Maj7,ChordDescriptor("c","m9Maj7","c"));

    // major seventh aug11
    QList<QString> Maj7Aug11 = QList<QString>() << "c" << "e" << "g" << "b" << "f#";
    RegisterNewChordType(Maj7Aug11,ChordDescriptor("c","Maj7(#11)","c"));

    // major ninth aug11
    QList<QString> Maj9Aug11 = QList<QString>() << "c" << "e" << "g" << "b" << "d" << "f#";
    RegisterNewChordType(Maj9Aug11,ChordDescriptor("c","Maj9(#11)","c"));

    // seventh dim9
    QList<QString> SevenDim9 = QList<QString>() << "c" << "e" << "g" << "bb" << "db";
    RegisterNewChordType(SevenDim9,ChordDescriptor("c","7(b9)","c"));

    // seventh aug5aug9
    QList<QString> SevenAug5Aug9 = QList<QString>() << "c" << "e" << "g#" << "bb" << "d#";
    RegisterNewChordType(SevenAug5Aug9,ChordDescriptor("c","7(#5)(#9)","c"));

    // seven aug5dim9 == inversion of m9(b5)
    // QList<QString> SevenAug5Dim9 = QList<QString>() << "c" << "e" << "g#" << "bb" << "db";
    // RegisterNewChordType(SevenAug5Dim9,ChordDescriptor("c","7(#5)(b9)","c"));

    // seven aug11 == inversion of 7(b5)
    //QList<QString> SevenAug11_2 = QList<QString>() << "c" << "e" << "g" << "bb" << "f#";
    //RegisterNewChordType(SevenAug11_2,ChordDescriptor("c","7(#11)","c"));

    // ninth aug11
    QList<QString> NineAug11 = QList<QString>() << "c" << "e" << "g" << "bb" << "d" << "f#";
    RegisterNewChordType(NineAug11,ChordDescriptor("c","9(#11)","c"));

    // seventh dim9aug11
    QList<QString> SevenDim9Aug11 = QList<QString>() << "c" << "e" << "g" << "bb" << "db" << "f#";
    RegisterNewChordType(SevenDim9Aug11,ChordDescriptor("c","7(b9)(#11)","c"));

    // seventh aug9aug11
    QList<QString> SevenAug9Aug11 = QList<QString>() << "c" << "e" << "g" << "bb" << "d#" << "f#";
    RegisterNewChordType(SevenAug9Aug11,ChordDescriptor("c","7(#9)(#11)","c"));

    // thirteen dim5
    QList<QString> ThirteenDim5 = QList<QString>() << "c" << "e" << "gb" << "bb" << "d" << "a";
    RegisterNewChordType(ThirteenDim5,ChordDescriptor("c","13(b5)","c"));

    // thirteen dim9
    QList<QString> ThirteenDim9 = QList<QString>() << "c" << "e" << "g" << "bb" << "dd" << "a";
    RegisterNewChordType(ThirteenDim9,ChordDescriptor("c","13(b9)","c"));

    // thirteen aug11
    QList<QString> ThirteenDim11 = QList<QString>() << "c" << "e" << "g" << "bb" << "d" << "f#" << "a";
    RegisterNewChordType(ThirteenDim11,ChordDescriptor("c","13(#11)","c"));

}

ChordDescriptor ChordRecognizer::RecognizeChord(const QList<QString> &TheoryNotes, bool &ChordRecognized) const
{
    QList<QString> SimplifiedChord = Chord(TheoryNotes).Simplify();
    QList<QList<QString> > Inversions = Chord(SimplifiedChord).CreateAllInversions();
    for (QList<QList<QString> >::const_iterator it = Inversions.begin(); it != Inversions.end(); ++it)
    {
        QList<int> IntervalPattern = Chord(*it).ToIntervalPattern();
        QString Key = Chord::PatternToKey(IntervalPattern);
        if (m_PatternToDescriptor.contains(Key))
        {
            ChordRecognized = true;
            QPair<ChordDescriptor, unsigned int> Info = m_PatternToDescriptor[Key];
            return ChordDescriptor((*it)[Info.second], Info.first.GetModifier(), TheoryNotes[0]);
        }
    }

    ChordRecognized = false;
    return ChordDescriptor(TheoryNotes[0],"major",TheoryNotes[0]);
}

void ChordRecognizer::RegisterNewChordType(const QList<QString> &TheoryNotes, const ChordDescriptor &ChordDescr)
{
    QList<QString> SimplifiedChord = Chord(TheoryNotes).Simplify();
    //if (SimplifiedChord != TheoryNotes)
    //{
    //    qDebug() << "Warning! Registering non-minimized chord " << ChordDescr.GetBaseName() << ","
    //             << ChordDescr.GetModifier() << "," << ChordDescr.GetSlash();
    //}

    QList<int> IntervalPattern = Chord(SimplifiedChord).ToIntervalPattern();
    QString Key = Chord::PatternToKey(IntervalPattern);
    unsigned int BaseNoteIndex = SimplifiedChord.indexOf(QString(TheoryNotes[0]));
    if (m_PatternToDescriptor.contains(Key))
        qDebug() << ChordDescr.GetBaseName() << "," << ChordDescr.GetModifier() << "," << ChordDescr.GetSlash() << " overwrites existing "
                 << m_PatternToDescriptor[Key].first.GetBaseName() << "," << m_PatternToDescriptor[Key].first.GetModifier()
                 << "," << m_PatternToDescriptor[Key].first.GetSlash();

    m_PatternToDescriptor[Key] = QPair<ChordDescriptor, unsigned int>(ChordDescr, BaseNoteIndex);
}


/*
---
TESTSUITE : ChordRecognizer
TYPE   : COLUMNBASED
LINK : [ chordrecognizer.cpp, chorddescriptor.cpp, chord.cpp, interval.cpp ]
INCLUDE: [ chordrecognizer.h, <QString>, <QHash>, <QList>, <QPair> ]
INCLUDEDIR : [ /usr/include/qt4,/usr/include/qt4/QtCore ]
BINLIB : [QtCore]
STUBS  :
PRE    : |
    ChordRecognizer R;
    QList<QString> Notes;
    ChordDescriptor D;
    bool Found = false;
POST   :
CODE   : [
  [
   [ 'recognition',  'Notes << $1'        , 'D = ChordDescriptor($1,$2,$3)', ~, 'EXPECT_EQ(R.RecognizeChord(Notes,Found), D)','EXPECT_EQ(Found, $1)'],
   [ 'e_power',      '"e",,"b"'           , '"e","perfectfifth","e"'       , ~, '.'                                          ,'true'                ],
   [ 'c_major',      '"c",,"e",,"g"'      , '"c","","c"'                   , ~, '.'                                          ,'true'                ],
   [ 'c_major_inv1', '"e",,"g",,"c"'      , '"c","","e"'                   , ~, '.'                                          ,'true'                ],
   [ 'c_major_inv2', '"e",,"g",,"c",,"e"' , '"c","","e"'                   , ~, '.'                                          ,'true'                ],
   [ 'f_major',      '"f",,"a",,"c"'      , '"f","","f"'                   , ~, '.'                                          ,'true'                ],
   [ 'eb_major',     '"eb",,"g",,"bb"'    , '"eb","","eb"'                 , ~, '.'                                          ,'true'                ],
   [ 'eb_minor',     '"gb",,"bb",,"eb"'   , '"eb","m","gb"'                , ~, '.'                                          ,'true'                ],
   [ 'dshrp_min_inv','"f#",,"a#",,"d#"'   , '"d#","m","f#"'                , ~, '.'                                          ,'true'                ],
   [ 'midi_minor',   '"c",,"d#",,"g"'     , '"c","m","c"'                  , ~, '.'                                          ,'true'                ],
  ],
]
*/

/*
---
TESTSUITE : ChordRecognizer_speed
TYPE   : RAW
LINK : [ chordrecognizer.cpp, chorddescriptor.cpp, chord.cpp, interval.cpp ]
INCLUDE: [ chordrecognizer.h, <QString>, <QHash>, <QList>, <QPair> ]
INCLUDEDIR : [ /usr/include/qt4,/usr/include/qt4/QtCore ]
BINLIB : [QtCore]
STUBS  :
CODE: |
    ChordRecognizer R;
    bool Found = false;
    QList<QString> TestChord;
    TestChord << "c" << "e" << "g" << "a" << "c";
    for (int i=0; i < 100000; ++i)
    {
        R.RecognizeChord(TestChord, Found);
        EXPECT_EQ(Found,true);
    }
*/
