#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    midi = new MIDI(this);
    connect(midi, SIGNAL(send_message(QString)), this, SLOT(updatelog(QString)));
    connect(midi, SIGNAL(add_input(QString)), this, SLOT(addinput(QString)));
    connect(midi, SIGNAL(add_output(QString)), this, SLOT(addoutput(QString)));
    midi->connect("Test");
    midi->start();
    ui->actionE_xit->setShortcut(QKeySequence::Quit);

    QComboBox combo(ui->synthList);
    combo.addItems(outputs);


}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);

    // Will need to add the MIDI termination necessities here. //
    midi->stop();
    sleep(1);   // give time for the other thread to finish up.
    delete midi;
    close();
}


// This is the SLOT for ui->button.  It's current function is to connect to ALSA MIDI
// and create a virtual port.  Next phase:  Allow the user to connect to a physical or
// virtual port (assuming virtual ports are supported on their OS).
void MainWindow::onButtonClick() {
    if(ui->button->text()=="Connect") {
        if(midi->connect(ui->connection->text())) {
            ui->button->setText("Disconnect");
            midi->start();
        }
    } else {
        midi->stop();
        ui->button->setText("Connect");
    }
}

void MainWindow::onViewChordAnalyzer() {
    ChordAnalyzer *ca = new ChordAnalyzer(this);
    ca->show();
}


void MainWindow::updatelog(QString message) {
    ui->msgarea->append(message);
}


void MainWindow::addinput(QString input) {
    ui->intputList->addItem(input);
}


void MainWindow::addoutput(QString output) {
    outputs << output;
}
