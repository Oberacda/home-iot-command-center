cmake_minimum_required(VERSION 3.15)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(home_iot_ctl_LIB_VERSION "1.0.0.0")

project(home_iot_ctl
        VERSION ${home_iot_ctl_LIB_VERSION}
        )


find_package(Threads REQUIRED)
find_package(PahoMqttCpp REQUIRED)

set(home_iot_ctl_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
