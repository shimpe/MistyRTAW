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


#include "chordmapper.h"
#include "chord.h"
#include "interval.h"

// a chord mapper replaces exotic chords with simpler chords

ChordMapper::ChordMapper()
{
    m_Map["minorsecond"] = QPair<QString,QString>("c","");
    m_Map["majorsecond"] = QPair<QString,QString>("d","m7");
    m_Map["minorthird"] = QPair<QString,QString>("c","m");
    m_Map["majorthird"] = QPair<QString,QString>("c","");
    m_Map["majorfourth"] = QPair<QString,QString>("f","");
    m_Map["augmentedfourth"] = QPair<QString,QString>("c","");
    m_Map["perfectfifth"] = QPair<QString,QString>("c","");
    m_Map["minorsixth"] = QPair<QString,QString>("ab","m");
    m_Map["majorsixth"] = QPair<QString,QString>("a","m");
    m_Map["minorseventh"] = QPair<QString,QString>("c","7");
    m_Map["majorseventh"] = QPair<QString,QString>("c","Maj7");
    m_Map[""] = QPair<QString,QString>("c","");
    m_Map["m"] = QPair<QString,QString>("c","m");
    m_Map["aug"] = QPair<QString,QString>("c","");
    m_Map["dim5"] = QPair<QString,QString>("c","");
    m_Map["sus2"] = QPair<QString,QString>("c","sus2");
    m_Map["sus4"] = QPair<QString,QString>("c","sus4");
    m_Map["7(omit5)"] = QPair<QString,QString>("c","7");
    m_Map["7(omit3)"] = QPair<QString,QString>("c","7");
    m_Map["Maj7(omit5)"] = QPair<QString,QString>("c","Maj7");
    m_Map["Maj7(omit3)"] = QPair<QString,QString>("c","Maj7");
    m_Map["m7(omit5)"] = QPair<QString,QString>("c","m7");
    m_Map["m7(omit3)"] = QPair<QString,QString>("c","m7");
    m_Map["add4"] = QPair<QString,QString>("c","sus4");
    m_Map["6"] = QPair<QString,QString>("a","m7");
    m_Map["m6"] = QPair<QString,QString>("c","m");
    m_Map["6/7"] = QPair<QString,QString>("c","7");
    m_Map["m6/7"] = QPair<QString,QString>("c","m7");
    m_Map["6/7sus"] = QPair<QString,QString>("c","7");
    m_Map["m(9)"] = QPair<QString,QString>("c","m");
    m_Map["7"] = QPair<QString,QString>("c","7");
    m_Map["Maj7"] = QPair<QString,QString>("c","Maj7");
    m_Map["m7"] = QPair<QString,QString>("c","m7");
    m_Map["7sus4"] = QPair<QString,QString>("c","7");
    m_Map["7(#5)"] = QPair<QString,QString>("c","7");
    m_Map["Maj7(#5)"] = QPair<QString,QString>("c","Maj7");
    m_Map["Maj7(b5)"] = QPair<QString,QString>("c","Maj7");
    m_Map["7(b5)"] = QPair<QString,QString>("c","7");
    m_Map["dim7"] = QPair<QString,QString>("c","7");
    m_Map["m7(b5)"] = QPair<QString,QString>("c","m7");
    m_Map["mMaj7"] = QPair<QString,QString>("c","m");
    m_Map["6(9)"] = QPair<QString,QString>("a","m");
    m_Map["m6(9)"] = QPair<QString,QString>("c","m");
    m_Map["m6(omit5)(9)"] = QPair<QString,QString>("c","m");
    m_Map["7(9)"] = QPair<QString,QString>("c","7");
    m_Map["7(#9)"] = QPair<QString,QString>("c","7");
    m_Map["7(b9)"] = QPair<QString,QString>("c","7");
    m_Map["7(#11)"] = QPair<QString,QString>("c","7");
    m_Map["Maj7(9)"] = QPair<QString,QString>("c","Maj7");
    m_Map["Maj7(13)"] = QPair<QString,QString>("c","Maj7");
    m_Map["Maj7(#11)"] = QPair<QString,QString>("c","Maj7");
    m_Map["m7(9)"] = QPair<QString,QString>("c","m7");
    m_Map["mMaj7(9)"] = QPair<QString,QString>("c","m");
    m_Map["7(13)"] = QPair<QString,QString>("c","7");
    m_Map["7(b13)"] = QPair<QString,QString>("c","7");
    m_Map["6/9"] = QPair<QString,QString>("c","");
    m_Map["Maj9"] = QPair<QString,QString>("c","Maj7");
    m_Map["9"] = QPair<QString,QString>("c","7");
    m_Map["m9"] = QPair<QString,QString>("c","m7");
    m_Map["9(#5)"] = QPair<QString,QString>("c","7");
    m_Map["9(b5)"] = QPair<QString,QString>("c","7");
    m_Map["m9(b5)"] = QPair<QString,QString>("c","m7");
    m_Map["m9(#5)"] = QPair<QString,QString>("c","m7");
    m_Map["11"] = QPair<QString,QString>("c","7");
    m_Map["Maj11"] = QPair<QString,QString>("c","Maj7");
    m_Map["m11"] = QPair<QString,QString>("c","m7");
    m_Map["m11(b5)"] = QPair<QString,QString>("c","m7");
    m_Map["m11(#5)"] = QPair<QString,QString>("c","m7");
    m_Map["13"] = QPair<QString,QString>("c","7");
    m_Map["13"] = QPair<QString,QString>("c","7");
    m_Map["Maj13"] = QPair<QString,QString>("c","Maj7");
    m_Map["m7(11)"] = QPair<QString,QString>("c","m7");
    m_Map["m7(13)"] = QPair<QString,QString>("c","m7");
    m_Map["m13"] = QPair<QString,QString>("c","m7");
    m_Map["m9Maj7"] = QPair<QString,QString>("c","Maj7");
    m_Map["Maj7(#11)"] = QPair<QString,QString>("c","Maj7");
    m_Map["Maj9(#11)"] = QPair<QString,QString>("c","Maj7");
    m_Map["7(b9)"] = QPair<QString,QString>("c","7");
    m_Map["7(#5)(#9)"] = QPair<QString,QString>("c","7");
    m_Map["7(#5)(b9)"] = QPair<QString,QString>("c","7");
    m_Map["7(#11)"] = QPair<QString,QString>("c","7");
    m_Map["9(#11)"] = QPair<QString,QString>("c","7");
    m_Map["7(b9)(#11)"] = QPair<QString,QString>("c","7");
    m_Map["7(#9)(#11)"] = QPair<QString,QString>("c","7");
    m_Map["13(b5)"] = QPair<QString,QString>("c","7");
    m_Map["13(b9)"] = QPair<QString,QString>("c","7");
    m_Map["13(#11)"] = QPair<QString,QString>("c","7");
}

ChordDescriptor ChordMapper::Lookup(const ChordDescriptor &ChordDescr) const
{
    if (m_Map.contains(ChordDescr.GetModifier()))
    {
        // transpose to get the notes right
        QPair<QString,QString> Mapped = m_Map[ChordDescr.GetModifier()];
        QString NewRootNote = Interval("c",Mapped.first).TransposeTo(ChordDescr.GetBaseName())[1];
        return ChordDescriptor(NewRootNote, Mapped.second, NewRootNote);
    }
    else
        return ChordDescr;
}


/*
---
TESTSUITE : ChordMapper
TYPE   : COLUMNBASED
LINK : [ chordmapper.cpp, chorddescriptor.cpp, interval.cpp, chord.cpp ]
INCLUDE: [ chordmapper.h, <QString>, <QHash>, <QList>, <QPair> ]
INCLUDEDIR : [ /usr/include/qt4,/usr/include/qt4/QtCore ]
BINLIB : [QtCore]
STUBS  :
PRE    : |
    ChordMapper M;
    QList<QString> Notes;
POST   :
CODE   : [
    [
        ['LookupTest'     , ~, 'EXPECT_EQ(M.Lookup(ChordDescriptor($1,$2,$3)), ChordDescriptor($4,$5,$6))'],
        ['Straightforward', ~, '"c","","c","c","","c"'                                                    ],
        ['Easy',            ~, '"e","","e","e","","e"'                                                    ],
        ['Transpose',       ~, '"f","majorsixth","f","d","m","d"'                                         ],
        ['Inverse',         ~, '"g","m","b","g","m","g"'                                                  ],
    ],
    ]
*/
