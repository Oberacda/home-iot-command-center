cmake_minimum_required(VERSION 3.14)

set(home_iot_ctl_LIB_TEST_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/test_home.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_device.cpp
        )

add_executable(home_iot_ctl_LIB_TEST
        ${home_iot_ctl_LIB_TEST_SOURCE_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
        )

target_link_libraries(home_iot_ctl_LIB_TEST
        PUBLIC home_iot_ctl_LIB
        PRIVATE GTest::GTest
        PRIVATE GTest::Main
        )
if(WIN32)
    add_custom_command(TARGET home_iot_ctl_LIB_TEST POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:home_iot_ctl_LIB>
            $<TARGET_FILE_DIR:home_iot_ctl_LIB_TEST>)

#[[    add_custom_command(TARGET home_iot_ctl_LIB_TEST POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_PROPERTY:GTest::GTest,IMPORTED_LOCATION_DEBUG>
            $<TARGET_FILE_DIR:home_iot_ctl_LIB_TEST>)
    add_custom_command(TARGET home_iot_ctl_LIB_TEST POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:GTest::Main>
            $<TARGET_FILE_DIR:home_iot_ctl_LIB_TEST>)]]
endif(WIN32)

if (home_iot_ctl_LIB_TESTING_COVERAGE_ENABLED)

    include(CodeCoverage)

    target_compile_options(home_iot_ctl_LIB_TEST
            PUBLIC -fprofile-arcs
            PUBLIC -ftest-coverage
            )
    target_link_options(home_iot_ctl_LIB_TEST
            PUBLIC --coverage
            )

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")


        target_link_libraries(home_iot_ctl_LIB_TEST
                PUBLIC gcov
                )


    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

    endif()

    set(COVERAGE_EXCLUDES
            "/usr/**/*"
            "${CMAKE_CURRENT_SOURCE_DIR}/*"
            )

    setup_target_for_coverage_lcov(
            NAME home_iot_ctl_LIB_TEST_COVERAGE
            EXECUTABLE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/HomeIotCtlTest"
            DEPENDENCIES home_iot_ctl_LIB_TEST
            BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
            EXCLUDE "'/usr/**/*'"
    )

endif(home_iot_ctl_LIB_TESTING_COVERAGE_ENABLED)

set_target_properties(home_iot_ctl_LIB_TEST
        PROPERTIES
        OUTPUT_NAME                 "HomeIotCtlTest"
        LANGUAGES                   CXX
        VERSION                     "${PROJECT_VERSION}"
        CXX_STANDARD                17
        RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test"
        )

if(WIN32)
    get_filename_component(OPENSSL_LIBRARY_DIR "${OPENSSL_CRYPTO_LIBRARY}" DIRECTORY)

    install(CODE 
        "include(BundleUtilities)\n
        fixup_bundle(\"$<TARGET_FILE:home_iot_ctl_LIB_TEST>\" \"\" \"${OPENSSL_LIBRARY_DIR}/../bin;${ZLIB_LIBRARY_DIR}/../bin;${LIBZIP_LIBRARY_DIR}/../bin;${Boost_LIBRARY_DIRS}\")"
        COMPONENT Runtime
        )

    install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DESTINATION .
        FILES_MATCHING PATTERN "*.dll")

endif(WIN32)

gtest_discover_tests(home_iot_ctl_LIB_TEST
        WORKING_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        )
