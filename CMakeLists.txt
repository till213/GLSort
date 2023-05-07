cmake_minimum_required(VERSION 3.20)

project(GLSort VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/MainWindow.ui
    src/Array.h src/Array.cpp
    src/Camera.h src/Camera.cpp
    src/Delay.h src/Delay.cpp
    src/DelayBar.h src/DelayBar.cpp
    src/DirWalk.h src/DirWalk.cpp
    src/Display.h src/Display.cpp
    src/GLSort.cpp
    src/GlutCallbacks.h src/GlutCallbacks.cpp
    src/Registry.h src/Registry.cpp
    src/Resources.h src/Resources.cpp
    src/Sort.h src/Sort.cpp
    src/Stat.h src/Stat.cpp
    src/Text.h src/Text.cpp
    src/TextScroller.h src/TextScroller.cpp
    src/Time.h src/Time.cpp
    src/TrackBall.h src/TrackBall.cpp
    src/Translation.h src/Translation.cpp
    src/Utils.h src/Utils.cpp
    src/Version.h src/Version.cpp
    src/Visual.h src/Visual.cpp
    src/WinInfo.h src/WinInfo.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GLSort
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GLSort APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GLSort SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GLSort
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GLSort PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(GLSort PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GLSort
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GLSort)
endif()
