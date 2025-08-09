cmake_minimum_required(VERSION 3.16)
project(macroapp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
endif()
 
# Find the required Qt libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Multimedia)

# Enable Qt's automatic tools for MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(src/audio src/core)

# Define the executable and list all source/UI files
add_executable(macroapp WIN32
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  src/core/macro_engine.cpp
  src/core/macro_engine.h
  src/core/global_hotkeys.cpp
  src/core/global_hotkeys.h
  src/ui/settings_dialog.cpp
  src/ui/settings_dialog.h
  src/ui/settings_dialog.ui
  src/ui/insert_event_dialog.cpp
  src/ui/insert_event_dialog.h
  src/ui/insert_event_dialog.ui
  src/ui/event_delegate.cpp
  src/ui/event_delegate.h
  src/audio/audio_decoder.cpp
  src/audio/audio_decoder.h
  sounds.qrc
)

# Link the Qt libraries to your executable
target_link_libraries(macroapp PRIVATE Qt6::Widgets Qt6::Gui Qt6::Multimedia)