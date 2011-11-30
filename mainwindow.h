#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <string>
#include "midi.h"

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
    void updatelog(QString message);

private:
    Ui::MainWindow *ui;
    MIDI *midi;
\
};

//void dataReceived(double time, std::vector<unsigned char> *message, void *userdata);

#endif // MAINWINDOW_H
