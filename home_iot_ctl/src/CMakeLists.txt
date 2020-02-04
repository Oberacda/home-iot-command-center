set(home_iot_ctl_LIB_PUBLIC_INCLUDE_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/home_iot_ctl_exports.hpp
        ${home_iot_ctl_INCLUDE_DIR}/iot/device.hpp
        ${home_iot_ctl_INCLUDE_DIR}/iot/home.hpp
        )
set(home_iot_ctl_LIB_PRIVATE_INCLUDE_FILES

        )

set(home_iot_ctl_LIB_INCLUDE_FILES
        ${home_iot_ctl_LIB_PUBLIC_INCLUDE_FILES}
        ${home_iot_ctl_LIB_PRIVATE_INCLUDE_FILES}
        )

set(home_iot_ctl_LIB_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/home.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mqtt_home.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/device.cpp
        )


add_library(home_iot_ctl_LIB SHARED
        ${home_iot_ctl_LIB_SOURCE_FILES}
        ${home_iot_ctl_LIB_INCLUDE_FILES}
        ${home_iot_ctl_LIB_RESOURCE_FILES}
        )

generate_export_header(home_iot_ctl_LIB
        BASE_NAME                   HomeIotCtl
        EXPORT_FILE_NAME            home_iot_ctl_exports.hpp
        EXPORT_MACRO_NAME           HOME_IOT_CTL_API
        DEPRECATED_MACRO_NAME       HOME_IOT_CTL_API_DEPRECATED
        NO_EXPORT_MACRO_NAME        HOME_IOT_CTL_API_NO_EXPORT
        NO_DEPRECATED_MACRO_NAME    HOME_IOT_CTL_API_NO_DEPRECATED
        )

target_include_directories(home_iot_ctl_LIB
        PUBLIC ${home_iot_ctl_INCLUDE_DIR}
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
        )

target_compile_options(home_iot_ctl_LIB
        PRIVATE -DHOME_IOT_CTL__LIB_EXPORTS=1
        PUBLIC  -fPIC
        PUBLIC  ${RAPIDJSON_CXX_FLAGS}
        )

target_link_libraries(home_iot_ctl_LIB
        PUBLIC PahoMqttCpp::paho-mqttpp3
        )

set_target_properties(home_iot_ctl_LIB
        PROPERTIES
        OUTPUT_NAME     "HomeIotCtl"
        LANGUAGES       CXX
        CXX_STANDARD    17
        VERSION         "${home_iot_ctl_LIB_VERSION}"
        PRIVATE_HEADER  "${home_iot_ctl_EXE_PRIVATE_INCLUDE_FILES}"
        PUBLIC_HEADER   "${home_iot_ctl_EXE_PUBLIC_INCLUDE_FILES}"
        )

if (home_iot_ctl_LIB_TESTING_COVERAGE_ENABLED)

        target_compile_options(home_iot_ctl_LIB
                PUBLIC -fprofile-arcs
                PUBLIC -ftest-coverage
                )

        target_link_options(home_iot_ctl_LIB
                PUBLIC --coverage
                )

        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")


                target_link_libraries(home_iot_ctl_LIB
                        PUBLIC gcov
                )


        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

        endif()

endif(home_iot_ctl_LIB_TESTING_COVERAGE_ENABLED)
