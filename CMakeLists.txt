cmake_minimum_required(VERSION 3.20)

project(
    GLSort
    VERSION 0.1
    DESCRIPTION "Visualisation of various sort algorithms with OpenGL"
    HOMEPAGE_URL "https://github.com/till213/GLSort"
    LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS: silence OpenGL deprecation warnings
add_definitions(-DGL_SILENCE_DEPRECATION)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

# Application libraries
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/Kernel)

# Application
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/GLSort)

# Plugins
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/SortAlgorithms)
