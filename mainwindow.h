#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/core/macro_engine.h"
#include "src/audio/audio_decoder.h"
#include <QStandardItemModel>
#include "src/ui/settings_dialog.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSoundEffect>
#include <QAudioSink>
#include <QBuffer>
#include "src/ui/event_delegate.h"
#include <QAbstractNativeEventFilter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

private slots:
    void on_recordButton_clicked();
    void on_playbackButton_clicked();
    void handleEventCaptured(const MacroEvent &event);
    void updateStatus(const QString &status);
    void on_settingsButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_insertEventButton_clicked();
    void deleteEvent(const QModelIndex &index);


private:
    void keyPressEvent(QKeyEvent *event) override;
    void loadSettings();
    void createTrayIcon();
    void createSoundEffects();
    void playSound(QByteArray *soundData, const QAudioFormat &format);
    void refreshEventViews();
    void registerHotkeys();
    void unregisterHotkeys();
    Ui::MainWindow *ui;
    AudioDecoder *audioDecoder;
    EventDelegate *eventDelegate;
    MacroEngine *macroEngine;
    QThread *engineThread;
    QStandardItemModel *keyboardEventsModel;
    QStandardItemModel *mouseEventsModel;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QByteArray recordStartSoundData;
    QByteArray recordStopSoundData;
    QByteArray playbackStartSoundData;
    QByteArray playbackStopSoundData;
    QByteArray saveSuccessfulSoundData;
    QAudioFormat audioFormat;
    bool isRecording = false;
    bool isPlaying = false;
};
#endif // MAINWINDOW_H