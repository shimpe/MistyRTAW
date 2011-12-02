#ifndef CHORDANALYZER_H
#define CHORDANALYZER_H

#include <QDialog>

namespace Ui {
    class ChordAnalyzer;
}

class ChordAnalyzer : public QDialog
{
    Q_OBJECT

public:
    explicit ChordAnalyzer(QWidget *parent = 0);
    ~ChordAnalyzer();

private:
    Ui::ChordAnalyzer *ui;
};

#endif // CHORDANALYZER_H
