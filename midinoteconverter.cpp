#include "midinoteconverter.h"

MidiNoteConverter::MidiNoteConverter()
{
    // initialize lookup table
    m_MidiNoteToString[CN1] = "C-1";
    m_MidiNoteToString[CsN1] = "C#-1";
    m_MidiNoteToString[DN1] = "D-1";
    m_MidiNoteToString[DsN1] = "D#-1";
    m_MidiNoteToString[EN1] = "E-1";
    m_MidiNoteToString[FN1] = "F-1";
    m_MidiNoteToString[FsN1] = "F#-1";
    m_MidiNoteToString[GN1] = "G-1";
    m_MidiNoteToString[GsN1] = "G#-1";

    m_MidiNoteToString[A0] = "A0";
    m_MidiNoteToString[As0] = "A#0";
    m_MidiNoteToString[B0] = "B0";
    m_MidiNoteToString[C0] = "C0";
    m_MidiNoteToString[Cs0] = "C#0";
    m_MidiNoteToString[D0] = "D0";
    m_MidiNoteToString[Ds0] = "D#0";
    m_MidiNoteToString[E0] = "E0";
    m_MidiNoteToString[F0] = "F0";
    m_MidiNoteToString[Fs0] = "F#0";
    m_MidiNoteToString[G0] = "G0";
    m_MidiNoteToString[Gs0] = "G#0";

    m_MidiNoteToString[A1] = "A1";
    m_MidiNoteToString[As1] = "A#1";
    m_MidiNoteToString[B1] = "B1";
    m_MidiNoteToString[C1] = "C1";
    m_MidiNoteToString[Cs1] = "C#1";
    m_MidiNoteToString[D1] = "D1";
    m_MidiNoteToString[Ds1] = "D#1";
    m_MidiNoteToString[E1] = "E1";
    m_MidiNoteToString[F1] = "F1";
    m_MidiNoteToString[Fs1] = "F#1";
    m_MidiNoteToString[G1] = "G1";
    m_MidiNoteToString[Gs1] = "G#1";

    m_MidiNoteToString[A2] = "A2";
    m_MidiNoteToString[As2] = "A#2";
    m_MidiNoteToString[B2] = "B2";
    m_MidiNoteToString[C2] = "C2";
    m_MidiNoteToString[Cs2] = "C#2";
    m_MidiNoteToString[D2] = "D2";
    m_MidiNoteToString[Ds2] = "D#2";
    m_MidiNoteToString[E2] = "E2";
    m_MidiNoteToString[F2] = "F2";
    m_MidiNoteToString[Fs2] = "F#2";
    m_MidiNoteToString[G2] = "G2";
    m_MidiNoteToString[Gs2] = "G#2";

    m_MidiNoteToString[A3] = "A3";
    m_MidiNoteToString[As3] = "A#3";
    m_MidiNoteToString[B3] = "B3";
    m_MidiNoteToString[C3] = "C3";
    m_MidiNoteToString[Cs3] = "C#3";
    m_MidiNoteToString[D3] = "D3";
    m_MidiNoteToString[Ds3] = "D#3";
    m_MidiNoteToString[E3] = "E3";
    m_MidiNoteToString[F3] = "F3";
    m_MidiNoteToString[Fs3] = "F#3";
    m_MidiNoteToString[G3] = "G3";
    m_MidiNoteToString[Gs3] = "G#3";

    m_MidiNoteToString[A4] = "A4";
    m_MidiNoteToString[As4] = "A#4";
    m_MidiNoteToString[B4] = "B4";
    m_MidiNoteToString[C4] = "C4";
    m_MidiNoteToString[Cs4] = "C#4";
    m_MidiNoteToString[D4] = "D4";
    m_MidiNoteToString[Ds4] = "D#4";
    m_MidiNoteToString[E4] = "E4";
    m_MidiNoteToString[F4] = "F4";
    m_MidiNoteToString[Fs4] = "F#4";
    m_MidiNoteToString[G4] = "G4";
    m_MidiNoteToString[Gs4] = "G#4";

    m_MidiNoteToString[A5] = "A5";
    m_MidiNoteToString[As5] = "A#5";
    m_MidiNoteToString[B5] = "B5";
    m_MidiNoteToString[C5] = "C5";
    m_MidiNoteToString[Cs5] = "C#5";
    m_MidiNoteToString[D5] = "D5";
    m_MidiNoteToString[Ds5] = "D#5";
    m_MidiNoteToString[E5] = "E5";
    m_MidiNoteToString[F5] = "F5";
    m_MidiNoteToString[Fs5] = "F#5";
    m_MidiNoteToString[G5] = "G5";
    m_MidiNoteToString[Gs5] = "G#5";

    m_MidiNoteToString[A6] = "A6";
    m_MidiNoteToString[As6] = "As6";
    m_MidiNoteToString[B6] = "B6";
    m_MidiNoteToString[C6] = "C6";
    m_MidiNoteToString[Cs6] = "C#6";
    m_MidiNoteToString[D6] = "D6";
    m_MidiNoteToString[Ds6] = "D#6";
    m_MidiNoteToString[E6] = "E6";
    m_MidiNoteToString[F6] = "F6";
    m_MidiNoteToString[Fs6] = "F#6";
    m_MidiNoteToString[G6] = "G6";
    m_MidiNoteToString[Gs6] = "G#6";

    m_MidiNoteToString[A7] = "A7";
    m_MidiNoteToString[As7] = "A#7";
    m_MidiNoteToString[B7] = "B7";
    m_MidiNoteToString[C7] = "C7";
    m_MidiNoteToString[Cs7] = "C#7";
    m_MidiNoteToString[D7] = "D7";
    m_MidiNoteToString[Ds7] = "D#7";
    m_MidiNoteToString[E7] = "E7";
    m_MidiNoteToString[F7] = "F7";
    m_MidiNoteToString[Fs7] = "F#7";
    m_MidiNoteToString[G7] = "G7";
    m_MidiNoteToString[Gs7] = "G#7";

    m_MidiNoteToString[A8] = "A8";
    m_MidiNoteToString[As8] = "As8";
    m_MidiNoteToString[B8] = "B8";
    m_MidiNoteToString[C8] = "C8";
    m_MidiNoteToString[Cs8] = "C#8";
    m_MidiNoteToString[D8] = "D8";
    m_MidiNoteToString[Ds8] = "D#8";
    m_MidiNoteToString[E8] = "E8";
    m_MidiNoteToString[F8] = "F8";
    m_MidiNoteToString[Fs8] = "F#8";
    m_MidiNoteToString[G8] = "G8";
    m_MidiNoteToString[Gs8] = "G#8";

    m_MidiNoteToString[A9] = "A9";
    m_MidiNoteToString[As9] = "As9";
    m_MidiNoteToString[B9] = "B9";
    m_MidiNoteToString[C9] = "C9";
    m_MidiNoteToString[Cs9] = "C#9";
    m_MidiNoteToString[D9] = "D9";
    m_MidiNoteToString[Ds9] = "D#9";
    m_MidiNoteToString[E9] = "E9";
    m_MidiNoteToString[F9] = "F9";
    m_MidiNoteToString[Fs9] = "F#9";
    m_MidiNoteToString[G9] = "G9";

    // initialize lookup table
    m_MidiNoteToTheoryNote[CN1]  = "c";
    m_MidiNoteToTheoryNote[CsN1] = "c#";
    m_MidiNoteToTheoryNote[DN1]  = "d";
    m_MidiNoteToTheoryNote[DsN1] = "d#";
    m_MidiNoteToTheoryNote[EN1]  = "e";
    m_MidiNoteToTheoryNote[FN1]  = "f";
    m_MidiNoteToTheoryNote[FsN1] = "f#";
    m_MidiNoteToTheoryNote[GN1]  = "g";
    m_MidiNoteToTheoryNote[GsN1] = "g#";

    m_MidiNoteToTheoryNote[A0]  = "a";
    m_MidiNoteToTheoryNote[As0] = "a#";
    m_MidiNoteToTheoryNote[B0]  = "b";
    m_MidiNoteToTheoryNote[C0]  = "c";
    m_MidiNoteToTheoryNote[Cs0] = "c#";
    m_MidiNoteToTheoryNote[D0]  = "d";
    m_MidiNoteToTheoryNote[Ds0] = "d#";
    m_MidiNoteToTheoryNote[E0]  = "e";
    m_MidiNoteToTheoryNote[F0]  = "f";
    m_MidiNoteToTheoryNote[Fs0] = "f#";
    m_MidiNoteToTheoryNote[G0]  = "g";
    m_MidiNoteToTheoryNote[Gs0] = "g#";

    m_MidiNoteToTheoryNote[A1]  = "a";
    m_MidiNoteToTheoryNote[As1] = "a#";
    m_MidiNoteToTheoryNote[B1]  = "b";
    m_MidiNoteToTheoryNote[C1]  = "c";
    m_MidiNoteToTheoryNote[Cs1] = "c#";
    m_MidiNoteToTheoryNote[D1]  = "d";
    m_MidiNoteToTheoryNote[Ds1] = "d#";
    m_MidiNoteToTheoryNote[E1]  = "e";
    m_MidiNoteToTheoryNote[F1]  = "f";
    m_MidiNoteToTheoryNote[Fs1] = "f#";
    m_MidiNoteToTheoryNote[G1]  = "g";
    m_MidiNoteToTheoryNote[Gs1] = "g#";

    m_MidiNoteToTheoryNote[A2]  = "a";
    m_MidiNoteToTheoryNote[As2] = "a#";
    m_MidiNoteToTheoryNote[B2]  = "b";
    m_MidiNoteToTheoryNote[C2]  = "c";
    m_MidiNoteToTheoryNote[Cs2] = "c#";
    m_MidiNoteToTheoryNote[D2]  = "d";
    m_MidiNoteToTheoryNote[Ds2] = "d#";
    m_MidiNoteToTheoryNote[E2]  = "e";
    m_MidiNoteToTheoryNote[F2]  = "f";
    m_MidiNoteToTheoryNote[Fs2] = "f#";
    m_MidiNoteToTheoryNote[G2]  = "g";
    m_MidiNoteToTheoryNote[Gs2] = "g#";

    m_MidiNoteToTheoryNote[A3]  = "a";
    m_MidiNoteToTheoryNote[As3] = "a#";
    m_MidiNoteToTheoryNote[B3]  = "b";
    m_MidiNoteToTheoryNote[C3]  = "c";
    m_MidiNoteToTheoryNote[Cs3] = "c#";
    m_MidiNoteToTheoryNote[D3]  = "d";
    m_MidiNoteToTheoryNote[Ds3] = "d#";
    m_MidiNoteToTheoryNote[E3]  = "e";
    m_MidiNoteToTheoryNote[F3]  = "f";
    m_MidiNoteToTheoryNote[Fs3] = "f#";
    m_MidiNoteToTheoryNote[G3]  = "g";
    m_MidiNoteToTheoryNote[Gs3] = "g#";

    m_MidiNoteToTheoryNote[A4]  = "a";
    m_MidiNoteToTheoryNote[As4] = "a#";
    m_MidiNoteToTheoryNote[B4]  = "b";
    m_MidiNoteToTheoryNote[C4]  = "c";
    m_MidiNoteToTheoryNote[Cs4] = "c#";
    m_MidiNoteToTheoryNote[D4]  = "d";
    m_MidiNoteToTheoryNote[Ds4] = "d#";
    m_MidiNoteToTheoryNote[E4]  = "e";
    m_MidiNoteToTheoryNote[F4]  = "f";
    m_MidiNoteToTheoryNote[Fs4] = "f#";
    m_MidiNoteToTheoryNote[G4]  = "g";
    m_MidiNoteToTheoryNote[Gs4] = "g#";

    m_MidiNoteToTheoryNote[A5]  = "a";
    m_MidiNoteToTheoryNote[As5] = "a#";
    m_MidiNoteToTheoryNote[B5]  = "b";
    m_MidiNoteToTheoryNote[C5]  = "c";
    m_MidiNoteToTheoryNote[Cs5] = "c#";
    m_MidiNoteToTheoryNote[D5]  = "d";
    m_MidiNoteToTheoryNote[Ds5] = "d#";
    m_MidiNoteToTheoryNote[E5]  = "e";
    m_MidiNoteToTheoryNote[F5]  = "f";
    m_MidiNoteToTheoryNote[Fs5] = "f#";
    m_MidiNoteToTheoryNote[G5]  = "g";
    m_MidiNoteToTheoryNote[Gs5] = "g#";

    m_MidiNoteToTheoryNote[A6]  = "a";
    m_MidiNoteToTheoryNote[As6] = "a#";
    m_MidiNoteToTheoryNote[B6]  = "b";
    m_MidiNoteToTheoryNote[C6]  = "c";
    m_MidiNoteToTheoryNote[Cs6] = "c#";
    m_MidiNoteToTheoryNote[D6]  = "d";
    m_MidiNoteToTheoryNote[Ds6] = "d#";
    m_MidiNoteToTheoryNote[E6]  = "e";
    m_MidiNoteToTheoryNote[F6]  = "f";
    m_MidiNoteToTheoryNote[Fs6] = "f#";
    m_MidiNoteToTheoryNote[G6]  = "g";
    m_MidiNoteToTheoryNote[Gs6] = "g#";

    m_MidiNoteToTheoryNote[A7]  = "a";
    m_MidiNoteToTheoryNote[As7] = "a#";
    m_MidiNoteToTheoryNote[B7]  = "b";
    m_MidiNoteToTheoryNote[C7]  = "c";
    m_MidiNoteToTheoryNote[Cs7] = "c#";
    m_MidiNoteToTheoryNote[D7]  = "d";
    m_MidiNoteToTheoryNote[Ds7] = "d#";
    m_MidiNoteToTheoryNote[E7]  = "e";
    m_MidiNoteToTheoryNote[F7]  = "f";
    m_MidiNoteToTheoryNote[Fs7] = "f#";
    m_MidiNoteToTheoryNote[G7]  = "g";
    m_MidiNoteToTheoryNote[Gs7] = "g#";

    m_MidiNoteToTheoryNote[A8]  = "a";
    m_MidiNoteToTheoryNote[As8] = "a#";
    m_MidiNoteToTheoryNote[B8]  = "b";
    m_MidiNoteToTheoryNote[C8]  = "c";
    m_MidiNoteToTheoryNote[Cs8] = "c#";
    m_MidiNoteToTheoryNote[D8]  = "d";
    m_MidiNoteToTheoryNote[Ds8] = "d#";
    m_MidiNoteToTheoryNote[E8]  = "e";
    m_MidiNoteToTheoryNote[F8]  = "f";
    m_MidiNoteToTheoryNote[Fs8] = "f#";
    m_MidiNoteToTheoryNote[G8]  = "g";
    m_MidiNoteToTheoryNote[Gs8] = "g#";

    m_MidiNoteToTheoryNote[A9]  = "a";
    m_MidiNoteToTheoryNote[As9] = "a#";
    m_MidiNoteToTheoryNote[B9]  = "b";
    m_MidiNoteToTheoryNote[C9]  = "c";
    m_MidiNoteToTheoryNote[Cs9] = "c#";
    m_MidiNoteToTheoryNote[D9]  = "d";
    m_MidiNoteToTheoryNote[Ds9] = "d#";
    m_MidiNoteToTheoryNote[E9]  = "e";
    m_MidiNoteToTheoryNote[F9]  = "f";
    m_MidiNoteToTheoryNote[Fs9] = "f#";
    m_MidiNoteToTheoryNote[G9]  = "g";
}

QString MidiNoteConverter::midiNoteToString(const notes &Note) const
{
    if (m_MidiNoteToString.size() > Note)
        return m_MidiNoteToString[Note];
    else
        return "Error:  Note not found.";
}

QString MidiNoteConverter::midiNoteToTheoryNote(const notes &Note) const
{
    if (m_MidiNoteToTheoryNote.size() > Note)
        return m_MidiNoteToTheoryNote[Note];
    else
        return "Error:  Note not found.";
}

/*
---
TESTSUITE : MidiNoteConverter
TYPE   : COLUMNBASED
LINK : [ midinoteconverter.cpp ]
INCLUDE: [ midinoteconverter.h, mididata.h, <QMap>, <QList> ]
INCLUDEDIR : [ /usr/include/qt4,/usr/include/qt4/QtCore ]
BINLIB : [QtCore]
STUBS  :
PRE    : |
  MidiNoteConverter M;
POST   :
CODE   : [
  [
   [ 'midiNoteToString',      ~, 'EXPECT_EQ(M.midiNoteToString($1), QString($2))'],
   [ 'firstvalue'      ,      ~, 'CN1,"C-1"'                                     ],
   [ 'middlevalue'     ,      ~, 'Cs7,"C#7"'                                     ],
   [ 'lastvalue'       ,      ~, 'G9,"G9"'                                       ],
   [ 'lastvalue2'      ,      ~, '(notes)127,"G9"'                               ],
   [ 'firstnonexistingvalue', ~, '(notes)128,"Error:  Note not found."'          ],
   [ 'nonexistingvalue',      ~, '(notes)250,"Error:  Note not found."'          ],
  ],
  [
   [ 'midiNoteToTheoryNote',  ~, 'EXPECT_EQ(M.midiNoteToTheoryNote($1), QString($2))'],
   [ 'firstvalue'      ,      ~, 'CN1,"c"'                                           ],
   [ 'middlevalue'     ,      ~, 'Cs7,"c#"'                                          ],
   [ 'lastvalue'       ,      ~, 'G9,"g"'                                            ],
   [ 'lastvalue2'      ,      ~, '(notes)127,"g"'                                    ],
   [ 'firstnonexistingvalue', ~, '(notes)128,"Error:  Note not found."'              ],
   [ 'nonexistingvalue',      ~, '(notes)250,"Error:  Note not found."'              ],
  ]
]
*/
