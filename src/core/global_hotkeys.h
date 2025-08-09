#ifndef GLOBALHOTKEYS_H
#define GLOBALHOTKEYS_H

#include <QObject>
#include <QAbstractNativeEventFilter>
#include <Windows.h>

#define HOTKEY_ID_RECORD 1
#define HOTKEY_ID_PLAYBACK 2

class GlobalHotkeys : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit GlobalHotkeys(QObject *parent = nullptr);
    ~GlobalHotkeys();

    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

signals:
    void recordHotkeyActivated();
    void playbackHotkeyActivated();

private:
    void registerHotkeys();
    void unregisterHotkeys();
};

#endif // GLOBALHOTKEYS_H