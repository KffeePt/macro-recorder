#include "global_hotkeys.h"
#include <QDebug>

GlobalHotkeys::GlobalHotkeys(QObject *parent) : QObject(parent)
{
    registerHotkeys();
}

GlobalHotkeys::~GlobalHotkeys()
{
    unregisterHotkeys();
}

void GlobalHotkeys::registerHotkeys()
{
    if (RegisterHotKey(NULL, HOTKEY_ID_RECORD, MOD_CONTROL, 'R'))
    {
        qDebug() << "Hotkey 'Ctrl+R' registered successfully.";
    }
    else
    {
        qDebug() << "Failed to register hotkey 'Ctrl+R'.";
    }

    if (RegisterHotKey(NULL, HOTKEY_ID_PLAYBACK, MOD_CONTROL, 'T'))
    {
        qDebug() << "Hotkey 'Ctrl+T' registered successfully.";
    }
    else
    {
        qDebug() << "Failed to register hotkey 'Ctrl+T'.";
    }
}

void GlobalHotkeys::unregisterHotkeys()
{
    UnregisterHotKey(NULL, HOTKEY_ID_RECORD);
    UnregisterHotKey(NULL, HOTKEY_ID_PLAYBACK);
}

bool GlobalHotkeys::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = static_cast<MSG*>(message);

    if (msg->message == WM_HOTKEY)
    {
        if (msg->wParam == HOTKEY_ID_RECORD)
        {
            emit recordHotkeyActivated();
            return true;
        }
        else if (msg->wParam == HOTKEY_ID_PLAYBACK)
        {
            emit playbackHotkeyActivated();
            return true;
        }
    }

    return false;
}