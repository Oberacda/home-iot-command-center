cmake_minimum_required(VERSION 3.15)
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
        )

project(home_iot_ctl_center_project)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GenerateExportHeader)

enable_testing()

add_subdirectory(home_iot_ctl)

option(home_iot_ctl_BUILD_QT_GUI "Build Qt5 GUI for the Command Center!" ON)

if (home_iot_ctl_BUILD_QT_GUI)
        add_subdirectory(home_iot_ctl_center)
endif(home_iot_ctl_BUILD_QT_GUI)

