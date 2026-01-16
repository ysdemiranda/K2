cmake_minimum_required( VERSION 4.2.0 )

project( K2 LANGUAGES CXX )

# K2 Version
set(K2_PLATFORM "${CMAKE_SYSTEM_PROCESSOR}")
set(K2_VERSION_MAJOR 0)
set(K2_VERSION_MINOR 1)
set(K2_VERSION_PATCH 0)

# libK2
add_library( K2
    source/kernel.cxx
    source/clock.cxx
    source/schedule.cxx
    source/task.cxx
)

# K2 meta generation
configure_file(source/k2.hxx.in ${CMAKE_CURRENT_LIST_DIR}/api/k2.hxx)

set_target_properties( K2 PROPERTIES
    OUTPUT_NAME "K2.${K2_PLATFORM}"
)
