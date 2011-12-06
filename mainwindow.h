#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QStringList>
#include <QComboBox>


#include <string>
#include "midi.h"
#include "chordanalyzer.h"

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

private:
    Ui::MainWindow *ui;
    MIDI *midi;
    QStringList outputs;
};

//void dataReceived(double time, std::vector<unsigned char> *message, void *userdata);

#endif // MAINWINDOW_H
