#include "mainwindow.h"
#include "ui_mainwindow.h" // This header is generated from mainwindow.ui

#include <QThread>
#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QKeyEvent>
#include "src/ui/insert_event_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hotkeys = new GlobalHotkeys(this);
    qApp->installNativeEventFilter(hotkeys);

    audioDecoder = new AudioDecoder(this);

    keyboardEventsModel = new QStandardItemModel(this);
    mouseEventsModel = new QStandardItemModel(this);
    ui->keyboardEventsView->setModel(keyboardEventsModel);
    ui->mouseEventsView->setModel(mouseEventsModel);

    eventDelegate = new EventDelegate(this);
    ui->keyboardEventsView->setItemDelegate(eventDelegate);
    ui->mouseEventsView->setItemDelegate(eventDelegate);

    connect(eventDelegate, &EventDelegate::deleteIndex, this, &MainWindow::deleteEvent);

    ui->keyboardEventsView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->mouseEventsView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    keyboardEventsModel->setHorizontalHeaderLabels({"Event", "Delay (ms)"});
    mouseEventsModel->setHorizontalHeaderLabels({"Event", "Position", "Delay (ms)"});

    macroEngine = new MacroEngine;
    engineThread = new QThread(this);
    macroEngine->moveToThread(engineThread);

    connect(engineThread, &QThread::finished, macroEngine, &QObject::deleteLater);

    connect(this, &MainWindow::destroyed, this, [=](){
        engineThread->quit();
        engineThread->wait();
    });

    connect(macroEngine, &MacroEngine::eventCaptured, this, &MainWindow::handleEventCaptured);
    connect(macroEngine, &MacroEngine::recordingStarted, this, [this](){ updateStatus("Recording..."); });
    connect(macroEngine, &MacroEngine::recordingStopped, this, [this](){ updateStatus("Idle"); });
    connect(macroEngine, &MacroEngine::playbackStarted, this, [this](){ updateStatus("Playing back..."); });
    connect(macroEngine, &MacroEngine::playbackStopped, this, [this](){
        if (macroEngine->isPlaybackEmpty()) {
            updateStatus("Nothing to play back.");
        } else {
            updateStatus("Idle");
        }
    });
    connect(hotkeys, &GlobalHotkeys::recordHotkeyActivated, this, &MainWindow::onRecordHotkey);
    connect(hotkeys, &GlobalHotkeys::playbackHotkeyActivated, this, &MainWindow::onPlaybackHotkey);


    engineThread->start();
    loadSettings();
    createTrayIcon();
    createSoundEffects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_recordButton_clicked()
{
    isRecording = !isRecording;
    if (isRecording) {
        if (isPlaying) {
            macroEngine->stopPlayback();
            isPlaying = false;
            ui->playbackButton->setText("Playback");
        }
        keyboardEventsModel->removeRows(0, keyboardEventsModel->rowCount());
        mouseEventsModel->removeRows(0, mouseEventsModel->rowCount());
        macroEngine->startRecording();
        playSound(&recordStartSoundData, audioFormat);
        ui->recordButton->setText("Stop Recording");
    } else {
        macroEngine->stopRecording();
        playSound(&recordStopSoundData, audioFormat);
        ui->recordButton->setText("Record");
    }
}

void MainWindow::on_playbackButton_clicked()
{
    isPlaying = !isPlaying;
    if (isPlaying) {
        if (isRecording) {
            macroEngine->stopRecording();
            isRecording = false;
            ui->recordButton->setText("Record");
        }
        int loopCount = ui->loopCountSpinBox->value();
        int loopIntervalValue = ui->loopIntervalSpinBox->value();
        QString unit = ui->intervalUnitComboBox->currentText();
        int loopInterval_ms = loopIntervalValue;

        if (unit == "s") {
            loopInterval_ms *= 1000;
        } else if (unit == "min") {
            loopInterval_ms *= 60000;
        } else if (unit == "hr") {
            loopInterval_ms *= 3600000;
        }

        macroEngine->setLoopSettings(loopCount, loopInterval_ms);
        macroEngine->startPlayback();
        playSound(&playbackStartSoundData, audioFormat);
        ui->playbackButton->setText("Stop Playback");
    } else {
        macroEngine->stopPlayback();
        playSound(&playbackStopSoundData, audioFormat);
        ui->playbackButton->setText("Playback");
    }
}

void MainWindow::handleEventCaptured(const MacroEvent &event)
{
    QList<QStandardItem *> rowItems;
    switch (event.type) {
        case KEY_PRESS:
            rowItems.append(new QStandardItem(QString("Key Press: %1").arg(QKeySequence(event.key_code).toString())));
            rowItems.append(new QStandardItem(QString::number(event.delay_ms)));
            keyboardEventsModel->appendRow(rowItems);
            break;
        case KEY_RELEASE:
            rowItems.append(new QStandardItem(QString("Key Release: %1").arg(QKeySequence(event.key_code).toString())));
            rowItems.append(new QStandardItem(QString::number(event.delay_ms)));
            keyboardEventsModel->appendRow(rowItems);
            break;
        case MOUSE_PRESS:
            rowItems.append(new QStandardItem("Mouse Press"));
            rowItems.append(new QStandardItem(QString("(%1, %2)").arg(event.position.x()).arg(event.position.y())));
            rowItems.append(new QStandardItem(QString::number(event.delay_ms)));
            mouseEventsModel->appendRow(rowItems);
            break;
        case MOUSE_RELEASE:
            rowItems.append(new QStandardItem("Mouse Release"));
            rowItems.append(new QStandardItem(QString("(%1, %2)").arg(event.position.x()).arg(event.position.y())));
            rowItems.append(new QStandardItem(QString::number(event.delay_ms)));
            mouseEventsModel->appendRow(rowItems);
            break;
        case MOUSE_MOVE:
            rowItems.append(new QStandardItem("Mouse Move"));
            rowItems.append(new QStandardItem(QString("(%1, %2)").arg(event.position.x()).arg(event.position.y())));
            rowItems.append(new QStandardItem(QString::number(event.delay_ms)));
            mouseEventsModel->appendRow(rowItems);
            break;
        case MOUSE_SCROLL:
            rowItems.append(new QStandardItem(QString("Mouse Scroll: %1").arg(event.scroll_delta)));
            rowItems.append(new QStandardItem(""));
            rowItems.append(new QStandardItem(QString::number(event.delay_ms)));
            mouseEventsModel->appendRow(rowItems);
            break;
        default:
            break;
    }
}

void MainWindow::updateStatus(const QString &status)
{
    ui->statusbar->showMessage(status);
}

void MainWindow::on_settingsButton_clicked()
{
    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        loadSettings();
        playSound(&saveSuccessfulSoundData, audioFormat);
    }
}

void MainWindow::loadSettings()
{
    QSettings settings("MySoft", "MacroApp");
    macroEngine->setMouseMovementRecordingDisabled(settings.value("behavior/disableMouseMovement", false).toBool());
    macroEngine->setMouseClickRecordingDisabled(settings.value("behavior/disableMouseClicks", false).toBool());
}

void MainWindow::on_saveButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Macro", QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.macros", "JSON Files (*.json)");
    if (filePath.isEmpty()) {
        return;
    }

    QJsonArray eventsArray;
    for (const auto& event : macroEngine->getRecordedEvents()) {
        QJsonObject eventObject;
        eventObject["type"] = event.type;
        eventObject["key_code"] = event.key_code;
        eventObject["button"] = (int)event.button;
        eventObject["x"] = event.position.x();
        eventObject["y"] = event.position.y();
        eventObject["scroll_delta"] = event.scroll_delta;
        eventObject["delay_ms"] = event.delay_ms;
        eventsArray.append(eventObject);
    }

    QJsonObject macroObject;
    macroObject["events"] = eventsArray;
    macroObject["loopCount"] = ui->loopCountSpinBox->value();
    macroObject["loopInterval"] = ui->loopIntervalSpinBox->value();
    macroObject["loopUnit"] = ui->intervalUnitComboBox->currentText();
    macroObject["disableMouseMovement"] = macroEngine->isMouseMovementRecordingDisabled();
    macroObject["disableMouseClicks"] = macroEngine->isMouseClickRecordingDisabled();


    QJsonDocument saveDoc(macroObject);
    QFile saveFile(filePath);
    if (saveFile.open(QIODevice::WriteOnly)) {
        saveFile.write(saveDoc.toJson());
        saveFile.close();
    }
}

void MainWindow::on_loadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load Macro", QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.macros", "JSON Files (*.json)");
    if (filePath.isEmpty()) {
        return;
    }

    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject macroObject = loadDoc.object();

    QJsonArray eventsArray = macroObject["events"].toArray();
    QVector<MacroEvent> loadedEvents;
    for (int i = 0; i < eventsArray.size(); ++i) {
        QJsonObject eventObject = eventsArray[i].toObject();
        MacroEvent event;
        event.type = (EventType)eventObject["type"].toInt();
        event.key_code = eventObject["key_code"].toInt();
        event.button = (Qt::MouseButton)eventObject["button"].toInt();
        event.position = QPoint(eventObject["x"].toInt(), eventObject["y"].toInt());
        event.scroll_delta = eventObject["scroll_delta"].toInt();
        event.delay_ms = eventObject["delay_ms"].toVariant().toLongLong();
        loadedEvents.append(event);
    }
    macroEngine->setRecordedEvents(loadedEvents);

    ui->loopCountSpinBox->setValue(macroObject["loopCount"].toInt());
    ui->loopIntervalSpinBox->setValue(macroObject["loopInterval"].toInt());
    ui->intervalUnitComboBox->setCurrentText(macroObject["loopUnit"].toString());

    // Refresh display
    keyboardEventsModel->removeRows(0, keyboardEventsModel->rowCount());
    mouseEventsModel->removeRows(0, mouseEventsModel->rowCount());
    for(const auto& event : loadedEvents) {
        handleEventCaptured(event);
    }
}

void MainWindow::onRecordHotkey()
{
    on_recordButton_clicked();
}

void MainWindow::onPlaybackHotkey()
{
    on_playbackButton_clicked();
}

void MainWindow::deleteEvent(const QModelIndex &index)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(const_cast<QAbstractItemModel*>(index.model()));
    if (model) {
        model->removeRow(index.row());
        QVector<MacroEvent> events = macroEngine->getRecordedEvents();
        events.removeAt(index.row());
        macroEngine->setRecordedEvents(events);
    }
}

void MainWindow::on_insertEventButton_clicked()
{
    InsertEventDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        MacroEvent event = dialog.getEventData();
        macroEngine->insertEvent(event);
        handleEventCaptured(event);
    }
}

void MainWindow::createSoundEffects()
{
    QFile recordStartFile(":/sounds/sounds/record_start.mp3");
    if (recordStartFile.open(QIODevice::ReadOnly)) {
        recordStartSoundData = audioDecoder->decodeFile(recordStartFile.readAll(), audioFormat);
        recordStartFile.close();
    }

    QFile recordStopFile(":/sounds/sounds/record_stop.mp3");
    if (recordStopFile.open(QIODevice::ReadOnly)) {
        recordStopSoundData = audioDecoder->decodeFile(recordStopFile.readAll(), audioFormat);
        recordStopFile.close();
    }

    QFile playbackStartFile(":/sounds/sounds/playback_start.mp3");
    if (playbackStartFile.open(QIODevice::ReadOnly)) {
        playbackStartSoundData = audioDecoder->decodeFile(playbackStartFile.readAll(), audioFormat);
        playbackStartFile.close();
    }

    QFile playbackStopFile(":/sounds/sounds/playback_stop.mp3");
    if (playbackStopFile.open(QIODevice::ReadOnly)) {
        playbackStopSoundData = audioDecoder->decodeFile(playbackStopFile.readAll(), audioFormat);
        playbackStopFile.close();
    }

    QFile saveSuccessfulFile(":/sounds/sounds/save_successful.mp3");
    if (saveSuccessfulFile.open(QIODevice::ReadOnly)) {
        saveSuccessfulSoundData = audioDecoder->decodeFile(saveSuccessfulFile.readAll(), audioFormat);
        saveSuccessfulFile.close();
    }
}

void MainWindow::playSound(QByteArray *soundData, const QAudioFormat &format)
{
    if (soundData->isEmpty() || !format.isValid()) {
        return;
    }

    QAudioSink *audioSink = new QAudioSink(QMediaDevices::defaultAudioOutput(), format, this);
    QBuffer *buffer = new QBuffer(soundData, this);
    buffer->open(QIODevice::ReadOnly);

    connect(audioSink, &QAudioSink::stateChanged, this, [=](QAudio::State state){
        if (state == QAudio::IdleState) {
            audioSink->deleteLater();
            buffer->deleteLater();
        }
    });

    audioSink->start(buffer);
}

void MainWindow::createTrayIcon()
{
    trayMenu = new QMenu(this);
    trayMenu->addAction("Show", this, &QWidget::showNormal);
    trayMenu->addAction("Quit", qApp, &QCoreApplication::quit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(this->windowIcon());
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (this->isVisible()) {
            this->hide();
        } else {
            this->showNormal();
        }
    }
}