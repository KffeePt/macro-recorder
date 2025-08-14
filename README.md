# Macro Recorder

A simple yet powerful macro recorder for Windows built with C++ and Qt. It allows you to record mouse and keyboard events and play them back, automating repetitive tasks with ease.

## Features

*   **Record and Playback**: Capture keyboard and mouse events and play them back accurately.
*   **Save and Load Macros**: Save your recorded macros to a file and load them back later.
*   **Global Hotkeys**: Start and stop recording and playback using global hotkeys (`Ctrl+R` and `Ctrl+T` respectively).
*   **Event Editing**: Manually insert, edit, and delete events in your macro sequence.
*   **Looping**: Play back your macros in a loop, with a configurable loop count and interval.
*   **Sound Feedback**: Get audible feedback when you start and stop recording and playback.
*   **System Tray Integration**: The application can be minimized to the system tray for easy access.

## Getting Started

### Prerequisites

Before you begin, ensure you have the following installed on your system:

*   **Qt 6**: You can download it from the [official Qt website](https://www.qt.io/download). Make sure to install the MinGW compiler version and add Qt's `bin` directory to your system's PATH.
*   **CMake**: You can download it from the [official CMake website](https://cmake.org/download/).
*   **MinGW**: This should be installed along with Qt. Ensure that the `mingw` `bin` directory is also in your system's PATH.

### Building the Application

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/KffeePt/macro-recorder.git
    cd macro-recorder
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake and compile:**
    ```bash
    cmake .. -G "MinGW Makefiles"
    mingw32-make
    ```

    This will create `macroapp.exe` in the `build` directory.

## Running the Application

After a successful build, you can run the application by executing the generated `.exe` file:

```bash
./macroapp.exe
```

Or by double-clicking on `macroapp.exe` in the `build` directory from your file explorer.

## Documentation

For more detailed information about the project's architecture, modules, and code, please see the full [developer documentation](./docs/README.md).

The documentation includes:

*   **Architecture Overview**: A high-level look at the application's structure.
*   **Core Module**: Details on the macro recording and playback engine.
*   **UI Module**: Information on the user interface components.
*   **Audio Module**: An explanation of the audio feedback system.
