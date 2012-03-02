#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    midi = new MistyMidi();
    loadPortNames();
    connect(ui->intputList, SIGNAL(currentTextChanged(QString)), midi, SLOT(input_changed(QString)));
    connect(midi, SIGNAL(send_message(QString)), this, SLOT(updatelog(QString)));
    ui->actionE_xit->setShortcut(QKeySequence::Quit);

    ui->synthList->setRowCount(1);
    ui->synthList->setItem(0, 0, new QTableWidgetItem("Piano", QTableWidgetItem::Type));
    SynthSelector *combo = new SynthSelector(ui->synthList, outputs);
    ui->synthList->setCellWidget(0, 1, combo);

    QDir mididir ("MIDI");

    if(mididir.exists()) {
        mididir.setFilter(QDir::Files | QDir::NoSymLinks);
        mididir.setNameFilters(QStringList("*.mid"));

        QFileInfoList files = mididir.entryInfoList();
        for(int i=0; i<files.size(); i++) {
            ui->accompanimentList->addItem(files.at(i).fileName());
        }
    } else {
        ui->accompanimentList->addItem(QString("Midi Directory %1 Not Found").arg(mididir.absolutePath()));
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::loadPortNames() {
    int i;

    // Load Inputs first...
    if(midi->getNumInputPorts() > 0) {
        for(i=0; i < midi->getNumInputPorts(); i++) {
            addinput(midi->getInputPortName(i));
        }
    }

    // ... then outputs.
    if(midi->getNumOutputPorts() > 0) {
        for(i=0; i < midi->getNumOutputPorts(); i++) {
            addoutput(midi->getOutputPortName(i));
        }
    }
}


void MainWindow::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);
    if (!outputs.empty()) {
        testmidi->stop();
        sleep(10);   // Wait for thread to finish
        delete testmidi;
    }
    close();
}


// This is the SLOT for ui->button.  It's current function is to connect to ALSA MIDI
// and create a virtual port.  Next phase:  Allow the user to connect to a physical or
// virtual port (assuming virtual ports are supported on their OS).
void MainWindow::onButtonClick() {
/*    if(ui->button->text()=="Connect") {
        if(midi->connect(ui->connection->text())) {
            ui->button->setText("Disconnect");
            midi->start();
        }
    } else {
        midi->stop();
        ui->button->setText("Connect");
    } */
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

void MainWindow::onAccompanimentSelection() {
    int tracks = 0;  int events = 0;
    QMessageBox qmb;

    MidiFile *midifile = new MidiFile();
    connect(midifile, SIGNAL(sendmessage(QString)), this, SLOT(updatelog(QString)));
    int errornum = midifile->LoadFile(ui->accompanimentList->currentItem()->text());

    /* while (tracks < midifile->numTracks()) {
        ui->msgarea->append(midifile->getTrackName(tracks));

        while(events < midifile->numEvents(tracks)) {
            ui->msgarea->append(midifile->getTrackEventText(tracks, events));
            events++;
        }
        tracks++;
    } */
    if(errornum==MidiFile_OK) {
        testmidi = new TestMidiOutput(midi->getMistyOutputs(), midifile);
        connect(testmidi, SIGNAL(send_message(QString)), this, SLOT(updatelog(QString)));
        testmidi->start();
    } else ui->msgarea->append(QString("Unable to load Midi file: %1").arg(midifile->getError(errornum)));
}
