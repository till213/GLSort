cmake_minimum_required(VERSION 3.16...3.23)

include(CMakePrintHelpers)

project(
    GLSortProject
    VERSION 0.1
    DESCRIPTION "Visualisation of various sort algorithms with OpenGL"
    HOMEPAGE_URL "https://github.com/till213/GLSort"
    LANGUAGES CXX
)

# Platform identifiers

# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks
string(COMPARE EQUAL "Windows" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_WINDOWS)
string(COMPARE EQUAL "Darwin" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_MACOS)
string(COMPARE EQUAL "Linux" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_LINUX)
cmake_print_variables(CMAKE_SYSTEM_NAME)

# Binary output locations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
if(${PLATFORM_IS_MACOS})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_NAME}.app/Contents/Frameworks)
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

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
