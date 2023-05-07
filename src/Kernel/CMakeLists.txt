set(LIBRARY_NAME "Kernel")

qt_add_library(${LIBRARY_NAME} SHARED)
add_library(Sort::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_compile_definitions(${LIBRARY_NAME}
    PRIVATE
        KERNEL_EXPORT
)

target_sources(${LIBRARY_NAME}
    PRIVATE
        include/Kernel/Array.h src/Array.cpp
        include/Kernel/Camera.h src/Camera.cpp
        include/Kernel/Delay.h src/Delay.cpp
        include/Kernel/DirWalk.h src/DirWalk.cpp
        include/Kernel/Registry.h src/Registry.cpp
        include/Kernel/Sort.h src/Sort.cpp
        include/Kernel/Stat.h src/Stat.cpp
        include/Kernel/Trackball.h src/Trackball.cpp
        include/Kernel/Utils.h src/Utils.cpp
        include/Kernel/Version.h src/Version.cpp
)
target_include_directories(${LIBRARY_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        include/Kernel
)
target_link_libraries(${LIBRARY_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::OpenGL
)

set_target_properties(${LIBRARY_NAME}
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)
