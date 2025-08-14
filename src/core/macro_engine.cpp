#include "macro_engine.h"
#include <QDebug>
#include <QCoreApplication>
#include <QThread>
#include <QTime>
#include <QKeySequence>
#include <QTimer>

#ifdef Q_OS_WIN
HHOOK MacroEngine::keyboardHook = nullptr;
HHOOK MacroEngine::mouseHook = nullptr;
MacroEngine* MacroEngine::instance = nullptr;
#endif

MacroEngine::MacroEngine(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_WIN
    instance = this;
#endif
}

MacroEngine::~MacroEngine()
{
    uninstallHook();
}

void MacroEngine::startRecording()
{
    if (isRecording) return;
    recordedEvents.clear();
    isRecording = installHook();
    if (isRecording) {
        emit recordingStarted();
    }
}

void MacroEngine::stopRecording()
{
    if (!isRecording) return;
    isRecording = false;
    uninstallHook();
    emit recordingStopped();
}

void MacroEngine::startPlayback()
{
    if (isPlaying || recordedEvents.isEmpty()) {
        if (recordedEvents.isEmpty()) {
            emit playbackStopped();
        }
        return;
    }
    isPlaying = true;
    emit playbackStarted();

    QThread* playbackThread = QThread::create([this](){
        int currentLoop = 0;
        bool infinite = (loopCount == 0);

        while(isPlaying && (infinite || currentLoop < loopCount)) {
            for (const auto& event : recordedEvents) {
                if (!isPlaying) break;

                if (event.delay_ms > 0) {
                    QThread::msleep(event.delay_ms);
                }

                switch (event.type) {
                    case KEY_PRESS:
                    case KEY_RELEASE:
                    {
#ifdef Q_OS_WIN
                        keybd_event(event.key_code, 0, (event.type == KEY_RELEASE) ? KEYEVENTF_KEYUP : 0, 0);
#endif
                        break;
                    }
                    case MOUSE_MOVE:
                    {
#ifdef Q_OS_WIN
                        SetCursorPos(event.position.x(), event.position.y());
#endif
                        break;
                    }
                    case MOUSE_PRESS:
                    case MOUSE_RELEASE:
                    {
#ifdef Q_OS_WIN
                        DWORD flags = 0;
                        if(event.button == Qt::LeftButton) flags = (event.type == MOUSE_PRESS) ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
                        if(event.button == Qt::RightButton) flags = (event.type == MOUSE_PRESS) ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP;
                        if(event.button == Qt::MiddleButton) flags = (event.type == MOUSE_PRESS) ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP;
                        mouse_event(flags, 0, 0, 0, 0);
#endif
                        break;
                    }
                    case MOUSE_SCROLL:
                    {
#ifdef Q_OS_WIN
                        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, event.scroll_delta, 0);
#endif
                        break;
                    }
                    default:
                        break;
                }
            }
            if (!isPlaying) break;
            
            currentLoop++;
            if (isPlaying && (infinite || currentLoop < loopCount)) {
                QThread::msleep(loopInterval_ms);
            }
        }

        isPlaying = false;
        emit playbackStopped();
    });
    connect(playbackThread, &QThread::finished, playbackThread, &QObject::deleteLater);
    playbackThread->start();
}

void MacroEngine::stopPlayback()
{
    isPlaying = false;
}

void MacroEngine::setLoopSettings(int count, int interval)
{
    loopCount = count;
    loopInterval_ms = interval;
}

bool MacroEngine::isPlaybackEmpty() const
{
    return recordedEvents.isEmpty();
}

void MacroEngine::setMouseMovementRecordingDisabled(bool disabled)
{
    disableMouseMovement = disabled;
}

void MacroEngine::setMouseClickRecordingDisabled(bool disabled)
{
    disableMouseClicks = disabled;
}

bool MacroEngine::isMouseMovementRecordingDisabled() const
{
    return disableMouseMovement;
}

bool MacroEngine::isMouseClickRecordingDisabled() const
{
    return disableMouseClicks;
}

QVector<MacroEvent> MacroEngine::getRecordedEvents() const
{
    return recordedEvents;
}

void MacroEngine::setRecordedEvents(const QVector<MacroEvent> &events)
{
    recordedEvents = events;
}

void MacroEngine::insertEvent(const MacroEvent &event)
{
    recordedEvents.append(event);
}

void MacroEngine::setRecordHotkey(const QKeySequence &hotkey)
{
    recordHotkey = hotkey;
}

void MacroEngine::removeLastEvent()
{
    if (!recordedEvents.isEmpty()) {
        recordedEvents.removeLast();
    }
}

void MacroEngine::cleanupHotkeyEvents()
{
    QVector<int> indicesToRemove;
    for (int i = 0; i < recordedEvents.size() - 1; ++i) {
        const auto& firstEvent = recordedEvents[i];
        const auto& secondEvent = recordedEvents[i+1];

        bool isCtrlR = (firstEvent.key_code == VK_CONTROL && secondEvent.key_code == 'R');
        bool isCtrlT = (firstEvent.key_code == VK_CONTROL && secondEvent.key_code == 'T');

        if ((isCtrlR || isCtrlT) && secondEvent.delay_ms < 500) {
            // Found a hotkey press, mark it and the corresponding release for removal
            indicesToRemove.append(i);
            indicesToRemove.append(i+1);

            // Find the corresponding key release events
            for (int j = i + 2; j < recordedEvents.size(); ++j) {
                if (recordedEvents[j].key_code == secondEvent.key_code && recordedEvents[j].type == KEY_RELEASE) {
                    indicesToRemove.append(j);
                    break;
                }
            }
            for (int j = i + 2; j < recordedEvents.size(); ++j) {
                if (recordedEvents[j].key_code == firstEvent.key_code && recordedEvents[j].type == KEY_RELEASE) {
                    indicesToRemove.append(j);
                    break;
                }
            }
        }
    }

    // Remove the marked indices in reverse order to avoid shifting
    std::sort(indicesToRemove.rbegin(), indicesToRemove.rend());
    for (int index : indicesToRemove) {
        recordedEvents.removeAt(index);
    }
}

void MacroEngine::setIgnoreHotkeys(bool ignore)
{
    ignoreHotkeys = ignore;
}

bool MacroEngine::isIgnoreHotkeys() const
{
    return ignoreHotkeys;
}

bool MacroEngine::installHook()
{
#ifdef Q_OS_WIN
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, lowLevelKeyboardProc, GetModuleHandle(NULL), 0);
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, lowLevelMouseProc, GetModuleHandle(NULL), 0);
    return keyboardHook && mouseHook;
#else
    return false; // Placeholder for other OS
#endif
}

void MacroEngine::uninstallHook()
{
#ifdef Q_OS_WIN
    if (keyboardHook) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = nullptr;
    }
    if (mouseHook) {
        UnhookWindowsHookEx(mouseHook);
        mouseHook = nullptr;
    }
#endif
}

#ifdef Q_OS_WIN
LRESULT CALLBACK MacroEngine::lowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && instance) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
        bool isKeyDown = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);

        if (instance->isIgnoreHotkeys()) {
            // Update key states
            if (p->vkCode == VK_LCONTROL || p->vkCode == VK_RCONTROL) {
                instance->ctrlDown = isKeyDown;
            } else if (p->vkCode == 'R') {
                instance->rDown = isKeyDown;
            } else if (p->vkCode == 'T') {
                instance->tDown = isKeyDown;
            }

            // If Ctrl is pressed with R or T, or if R or T is pressed with Ctrl, filter the event.
            if ((instance->ctrlDown && (p->vkCode == 'R' || p->vkCode == 'T')) ||
                (isKeyDown && (instance->rDown || instance->tDown) && (p->vkCode == VK_LCONTROL || p->vkCode == VK_RCONTROL))) {
                return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
            }

            // Also filter the key release of the hotkey components.
            if (!isKeyDown) {
                if ((p->vkCode == 'R' && GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
                    (p->vkCode == 'T' && GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
                    ((p->vkCode == VK_LCONTROL || p->vkCode == VK_RCONTROL) && (GetAsyncKeyState('R') & 0x8000 || GetAsyncKeyState('T') & 0x8000))) {
                    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
                }
            }
        }

        if (instance->isRecording) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN || wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                MacroEvent event;
                event.type = isKeyDown ? KEY_PRESS : KEY_RELEASE;
                event.key_code = p->vkCode;
                static QTime lastEventTime = QTime::currentTime();
                event.delay_ms = lastEventTime.msecsTo(QTime::currentTime());
                lastEventTime = QTime::currentTime();
                instance->recordedEvents.append(event);
                emit instance->eventCaptured(event);
            }
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MacroEngine::lowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && instance && instance->isRecording) {
        MSLLHOOKSTRUCT *p = (MSLLHOOKSTRUCT *)lParam;
        MacroEvent event;
        event.position = QPoint(p->pt.x, p->pt.y);
        static QTime lastEventTime = QTime::currentTime();
        event.delay_ms = lastEventTime.msecsTo(QTime::currentTime());
        lastEventTime = QTime::currentTime();

        switch (wParam) {
            case WM_LBUTTONDOWN:
                if (instance->disableMouseClicks) return CallNextHookEx(mouseHook, nCode, wParam, lParam);
                event.type = MOUSE_PRESS;
                event.button = Qt::LeftButton;
                break;
            case WM_LBUTTONUP:
                if (instance->disableMouseClicks) return CallNextHookEx(mouseHook, nCode, wParam, lParam);
                event.type = MOUSE_RELEASE;
                event.button = Qt::LeftButton;
                break;
            case WM_RBUTTONDOWN:
                if (instance->disableMouseClicks) return CallNextHookEx(mouseHook, nCode, wParam, lParam);
                event.type = MOUSE_PRESS;
                event.button = Qt::RightButton;
                break;
            case WM_RBUTTONUP:
                if (instance->disableMouseClicks) return CallNextHookEx(mouseHook, nCode, wParam, lParam);
                event.type = MOUSE_RELEASE;
                event.button = Qt::RightButton;
                break;
            case WM_MOUSEMOVE:
                if (instance->disableMouseMovement) return CallNextHookEx(mouseHook, nCode, wParam, lParam);
                event.type = MOUSE_MOVE;
                break;
            case WM_MOUSEWHEEL:
                event.type = MOUSE_SCROLL;
                event.scroll_delta = GET_WHEEL_DELTA_WPARAM(p->mouseData);
                break;
            default:
                return CallNextHookEx(mouseHook, nCode, wParam, lParam);
        }
        instance->recordedEvents.append(event);
        emit instance->eventCaptured(event);
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
#endif