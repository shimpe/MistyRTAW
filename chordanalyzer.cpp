#include "chordanalyzer.h"
#include "ui_chordanalyzer.h"

ChordAnalyzer::ChordAnalyzer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChordAnalyzer)
{
    ui->setupUi(this);
}

ChordAnalyzer::~ChordAnalyzer()
{
    delete ui;
}
