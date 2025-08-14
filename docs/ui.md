# UI Module

The UI module contains all the graphical user interface components of the application.

## Files

*   `event_delegate.h` / `event_delegate.cpp`: Implements a custom delegate for rendering items in the event list views.
*   `insert_event_dialog.h` / `insert_event_dialog.cpp` / `insert_event_dialog.ui`: Defines the dialog for manually inserting new macro events.
*   `settings_dialog.h` / `settings_dialog.cpp` / `settings_dialog.ui`: Defines the application settings dialog.
*   `mainwindow.h` / `mainwindow.cpp` / `mainwindow.ui`: The main application window.

## Key Classes

### `MainWindow`

The `MainWindow` class is the heart of the user interface, acting as the central hub that connects all other UI components and the core application logic. It's responsible for the main application window, the system tray icon, and for orchestrating the interactions between the user and the `MacroEngine`.

#### Implementation Details

**Initialization:**
- The constructor sets up the UI, instantiates the `MacroEngine`, `GlobalHotkeys`, and `AudioDecoder`.
- It moves the `MacroEngine` to a separate thread (`engineThread`) to ensure the GUI remains responsive during recording and playback.
- It connects the signals from the `MacroEngine` and `GlobalHotkeys` to the corresponding slots in the `MainWindow` (e.g., `handleEventCaptured`, `onRecordHotkey`).
- It sets up the models for the keyboard and mouse event views (`QStandardItemModel`) and assigns the custom `EventDelegate` for rendering.
- It creates the system tray icon and loads the initial settings and sound effects.

**User Actions:**
- The `on_recordButton_clicked()` and `on_playbackButton_clicked()` slots handle the main user interactions, starting and stopping the recording and playback processes in the `MacroEngine`.
- `on_saveButton_clicked()` and `on_loadButton_clicked()` handle the serialization of the macro events to and from JSON files.
- `on_settingsButton_clicked()` opens the `SettingsDialog`.
- `on_insertEventButton_clicked()` opens the `InsertEventDialog`.

**Event Handling:**
- `handleEventCaptured()` receives the `MacroEvent` from the `MacroEngine` and adds a new item to the appropriate list view (keyboard or mouse).
- `deleteEvent()` is a slot connected to the `EventDelegate`'s `deleteIndex` signal, allowing the user to remove events from the list.

**Key Responsibilities:**
- Provides buttons to start/stop recording and playback.
- Displays the list of recorded events.
- Allows saving and loading macros.
- Opens the settings and insert event dialogs.
- Manages the system tray icon and menu.
- Plays sound effects for feedback.

### `SettingsDialog`

This class provides a dialog window that allows users to configure various application settings. This includes customizing the global hotkeys for recording and playback, setting the default loop count and interval for macros, and managing other application preferences.

#### Implementation Details
- The dialog uses `QSettings` to persist application settings between sessions.
- `loadSettings()` is called in the constructor to populate the UI controls with the saved settings.
- When the user clicks "OK", the `accept()` slot is called, which first calls `saveSettings()` to write the current UI values back to the `QSettings` file.

**Key Responsibilities:**
- Loads the current settings when opened.
- Saves the modified settings when the user clicks "OK".

### `InsertEventDialog`

This dialog provides a user-friendly way to manually insert new events into a macro sequence. It's particularly useful for fine-tuning existing macros with precise actions or for building a macro from scratch without having to perform the actions in real-time.

#### Implementation Details
- The `getEventData()` method is called by the `MainWindow` after the dialog is accepted.
- It constructs a `MacroEvent` struct from the values entered into the UI controls (event type, key, delay) and returns it.

**Public Methods:**
- `getEventData()`: Returns the `MacroEvent` created by the user in the dialog.

### `EventDelegate`

The `EventDelegate` is a crucial component for creating a polished and user-friendly experience. It's responsible for the custom rendering of items in the event list views, allowing for a much richer display than the standard Qt item views. This includes drawing icons, custom text formatting, and handling user interactions like clicking a "delete" button on an individual event.

#### Implementation Details
- The `paint()` method is overridden to draw a trash icon on the right side of the last column of each item.
- The `editorEvent()` method is overridden to detect mouse clicks on the trash icon. When a click is detected, it emits the `deleteIndex` signal, passing the index of the item to be deleted.

**Public Methods:**
- `paint(...)`: Custom paints the items in the event list.
- `editorEvent(...)`: Handles events like mouse clicks on the items (e.g., to delete an event).

**Signals:**
- `deleteIndex(const QModelIndex &index)`: Emitted when the user clicks the delete icon on an event item.