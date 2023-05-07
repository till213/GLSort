set(MODULE_NAME "BubbleSort")

qt_add_library(${MODULE_NAME} MODULE)
add_library(Sky::${MODULE_NAME} ALIAS ${MODULE_NAME})

target_sources(${MODULE_NAME}
    PRIVATE
        src/BubbleSort.h src/BubbleSort.cpp
)
target_link_libraries(${MODULE_NAME}
    PRIVATE
        Sort::Kernel
)
