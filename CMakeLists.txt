cmake_minimum_required(VERSION 3.15)
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
        )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(home_iot_command_center)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(PahoMqttCpp REQUIRED)


set(home_iot_command_center_VERSION "1.0.0.1")

set(home_iot_command_center_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${home_iot_command_center_INCLUDE_DIR})

add_subdirectory(src)

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY   ${PROJECT_DESCRIPTION})
SET(CPACK_PACKAGE_VENDOR                "D4ve")
SET(CPACK_PACKAGE_DESCRIPTION_FILE      "${CMAKE_CURRENT_SOURCE_DIR}/Readme.txt")
SET(CPACK_RESOURCE_FILE_LICENSE         "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR         ${PROJECT_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR         ${PROJECT_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH         ${PROJECT_VERSION_PATCH})

IF (WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    SET(CPACK_PACKAGE_ICON              "${CMAKE_CURRENT_SOURCE_DIR}/resources\\\\appicon.ico")
    SET(CPACK_NSIS_INSTALLED_ICON_NAME  "bin\\\\BorderlandsSaveEditor.exe")
    SET(CPACK_NSIS_DISPLAY_NAME         ${PROJECT_NAME})
    SET(CPACK_NSIS_HELP_LINK            "http:\\\\\\\\www.d4ve.org")
    SET(CPACK_NSIS_URL_INFO_ABOUT       "http:\\\\\\\\www.d4ve.com")
    SET(CPACK_NSIS_CONTACT              "david.oberacker@student.kit.edu")
    SET(CPACK_NSIS_MODIFY_PATH          ON)
ELSE (WIN32 AND NOT UNIX)
    SET(CPACK_STRIP_FILES               "bin/BorderlandsSaveEditor")
    SET(CPACK_SOURCE_STRIP_FILES        "")
ENDIF (WIN32 AND NOT UNIX)

INCLUDE(CPack)