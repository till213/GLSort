set(PROJECT_SOURCES
    src/DelayBar.h src/DelayBar.cpp
    src/Display.h src/Display.cpp
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/MainWindow.ui
    src/Resources.h src/Resources.cpp
    src/GLSort.cpp
    src/GlutCallbacks.h src/GlutCallbacks.cpp
    src/SortVisualWidget.h src/SortVisualWidget.cpp
    src/Text.h src/Text.cpp
    src/Text.h src/Text.cpp
    src/TextScroller.h src/TextScroller.cpp
    src/Timer.h src/Timer.cpp
    src/Translation.h src/Translation.cpp
    src/Visual.h src/Visual.cpp
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
#                 ${CMAKE_CURRENT_LIST_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GLSort SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/android")
    else()
        add_executable(GLSort
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(GLSort
    INTERFACE

    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src
)
target_link_libraries(GLSort
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::OpenGL
        Qt${QT_VERSION_MAJOR}::OpenGLWidgets
        -lGLU
        Sort::Kernel
)

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

