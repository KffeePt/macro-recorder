#ifndef MACRO_ENGINE_H
#define MACRO_ENGINE_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QThread>
#include <QKeySequence>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

enum EventType { KEY_PRESS, KEY_RELEASE, MOUSE_MOVE, MOUSE_PRESS, MOUSE_RELEASE, MOUSE_SCROLL, WAIT };

struct MacroEvent {
    EventType type;
    int key_code;
    Qt::MouseButton button;
    QPoint position;
    int scroll_delta;
    qint64 delay_ms;
};

class MacroEngine : public QObject
{
    Q_OBJECT
public:
    explicit MacroEngine(QObject *parent = nullptr);
    ~MacroEngine();

    void startRecording();
    void stopRecording();
    void startPlayback();
    void stopPlayback();
    void setLoopSettings(int count, int interval);
    bool isPlaybackEmpty() const;
    bool getIsRecording() const { return isRecording; }
    bool getIsPlaying() const { return isPlaying; }
    void setMouseMovementRecordingDisabled(bool disabled);
    void setMouseClickRecordingDisabled(bool disabled);
    bool isMouseMovementRecordingDisabled() const;
    bool isMouseClickRecordingDisabled() const;
    QVector<MacroEvent> getRecordedEvents() const;
    void setRecordedEvents(const QVector<MacroEvent> &events);
    void insertEvent(const MacroEvent &event);
    void setRecordHotkey(const QKeySequence &hotkey);
    void removeLastEvent();
    void cleanupHotkeyEvents();
    void setIgnoreHotkeys(bool ignore);
    bool isIgnoreHotkeys() const;

signals:
    void eventCaptured(const MacroEvent &event);
    void recordingStarted();
    void recordingStopped();
    void playbackStarted();
    void playbackStopped();
private:
    bool installHook();
    void uninstallHook();

#ifdef Q_OS_WIN
    static LRESULT CALLBACK lowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK lowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);
#endif

    QVector<MacroEvent> recordedEvents;
    bool isRecording = false;
    bool isPlaying = false;
    int loopCount = 1;
    int loopInterval_ms = 0;
    bool disableMouseMovement = false;
    bool disableMouseClicks = false;
    QKeySequence recordHotkey;
    bool ignoreHotkeys = true;

    // Track combo state to filter hotkeys cleanly
    bool ctrlDown = false;
    bool rDown = false;
    bool tDown = false;

#ifdef Q_OS_WIN
    static HHOOK keyboardHook;
    static HHOOK mouseHook;
    static MacroEngine* instance;
#endif
};

#endif // MACRO_ENGINE_H