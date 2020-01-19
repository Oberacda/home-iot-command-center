set(home_iot_command_center_EXE_INCLUDE_FILES
        ${home_iot_command_center_INCLUDE_DIR}/main.hpp
        ${home_iot_command_center_INCLUDE_DIR}/mymodel.hpp
        )

set(home_iot_command_center_EXE_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mymodel.cpp
        )

if (WIN32)
    set(home_iot_command_center_EXE_SOURCE_FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/main_windows.cpp
            ${home_iot_command_center_EXE_SOURCE_FILES}
            )

    include(generate_product_version)
    generate_product_version(
            home_iot_command_center_EXE_VersionFilesOutputVariable
            NAME                ${PROJECT_NAME}
            ICON                ${home_iot_command_center_EXE_RESOURCE_DIR}/appicon.ico
            VERSION_MAJOR       ${CMAKE_PROJECT_VERSION_MAJOR}
            VERSION_MINOR       ${CMAKE_PROJECT_VERSION_MINOR}
            VERSION_PATCH       ${CMAKE_PROJECT_VERSION_PATCH}
            VERSION_REVISION    ${CMAKE_PROJECT_VERSION_TWEAK}
    )
    set(home_iot_command_center_EXE_RESOURCE_FILES
            ${home_iot_command_center_EXE_RESOURCE_FILES}
            ${home_iot_command_center_EXE_VersionFilesOutputVariable}
            )
endif (WIN32)

add_executable(home_iot_command_center_EXE
        ${home_iot_command_center_EXE_SOURCE_FILES}
        ${home_iot_command_center_EXE_INCLUDE_FILES}
        )

target_link_libraries(home_iot_command_center_EXE
        Qt5::Widgets
        PahoMqttCpp::paho-mqttpp3
        OpenSSL::SSL
        OpenSSL::Crypto
        )
set_target_properties(home_iot_command_center_EXE
        PROPERTIES
        OUTPUT_NAME     "HomeIotCommandCenter"
        LANGUAGES       CXX
        VERSION         "${CMAKE_PROJECT_VERSION}"
        AUTOMOC         ON
        AUTOUIC         ON
        AUTORCC         ON
        )

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")

if (WIN32)
    set_target_properties(home_iot_command_center_EXE
            PROPERTIES
            WIN32_EXECUTABLE ON
            )

    add_custom_command(TARGET home_iot_command_center_EXE POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE:home_iot_command_center_EXE>"
            COMMENT "Running windeployqt..."
            )
elseif (APPLE)
    add_custom_command(TARGET home_iot_command_center_EXE POST_BUILD
            COMMAND "${MACDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE_DIR:home_iot_command_center_EXE>/../.."
            -always-overwrite
            COMMENT "Running macdeployqt..."
            )

    set(MACOSX_BUNDLE_ICON_FILE             appicon.icns)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER        "com.d4ve.iot.HomeIotCommandCenter")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING   ${home_iot_command_center_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING  ${home_iot_command_center_VERSION})
    set(MACOSX_BUNDLE_BUNDLE_NAME           HomeIotCommandCenter)

    set_target_properties(home_iot_command_center_EXE
            PROPERTIES
            MACOSX_BUNDLE               ON
            MACOSX_BUNDLE_INFO_PLIST    ${home_iot_command_center_EXE_RESOURCE_DIR}/MacOSXBundleInfo.plist.in
            RESOURCE                    "${home_iot_command_center_EXE_RESOURCE_FILES}"
            )

endif ()

get_filename_component(OPENSSL_LIBRARY_DIR "${OPENSSL_SSL_LIBRARY}" DIRECTORY)

#install(TARGETS home_iot_command_center_EXE
#        RUNTIME
#        DESTINATION bin
#        COMPONENT Runtime
#        BUNDLE
#        DESTINATION .
#        COMPONENT Runtime
#        )

if(WIN32)
    install(CODE
            "include(BundleUtilities)\n
        fixup_bundle(\"$<TARGET_FILE:home_iot_command_center_EXE>\" \"\" \"${OPENSSL_LIBRARY_DIR}/../bin\")"
            COMPONENT Runtime
            )

    install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            DESTINATION .
            FILES_MATCHING PATTERN "*.dll")

endif(WIN32)