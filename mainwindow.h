#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStringList>
#include <QComboBox>
#include <QDir>

#include <string>

#include "midi.h"
#include "midifile.h"
#include "chordanalyzer.h"
#include "synthselector.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void closeEvent(QCloseEvent *event);
    void onButtonClick();
    void onViewChordAnalyzer();
    void updatelog(QString message);
    void addinput(QString input);
    void addoutput(QString output);
    void onAccompanimentSelection();

private:
    Ui::MainWindow *ui;
    MIDI *midi;
    QStringList outputs;
};


#endif // MAINWINDOW_H
