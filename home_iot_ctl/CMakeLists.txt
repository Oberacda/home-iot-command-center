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

find_package(GTest)

find_package(Doxygen)
# first we can indicate the documentation build as an option and set it to ON by default
option(home_iot_ctl_BUILD_DOC "Build documentation" ON)

if (DOXYGEN_FOUND AND home_iot_ctl_BUILD_DOC)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/resources/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(home_iot_ctl_LIB_DOC
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND AND home_iot_ctl_BUILD_DOC)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND AND home_iot_ctl_BUILD_DOC)

set(home_iot_ctl_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(home_iot_ctl_LIB_TESTING_ENABLED "Enabled testing of the project!" ON)
option(home_iot_ctl_LIB_TESTING_COVERAGE_ENABLED "Enabled test coverage of the project!" ON)
if(home_iot_ctl_LIB_TESTING_COVERAGE_ENABLED AND NOT home_iot_ctl_LIB_TESTING_ENABLED)
    message(ERROR "Coverage can only be enabled when testing is enabled!")
endif(home_iot_ctl_LIB_TESTING_COVERAGE_ENABLED AND NOT home_iot_ctl_LIB_TESTING_ENABLED)

add_subdirectory(src)

if (GTEST_FOUND AND home_iot_ctl_LIB_TESTING_ENABLED)
    enable_testing()
    add_subdirectory(test)

    message(STATUS "Testing enabled!")
endif (GTEST_FOUND AND home_iot_ctl_LIB_TESTING_ENABLED)


