cmake_minimum_required(VERSION 3.2)

include_directories("${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/tests" ${CONAN_INCLUDE_DIRS})

link_libraries("boost_unit_test_framework")

add_executable("test_run"
    "test_run.cpp"
    )

add_executable("test_settings"
    "test_settings.cpp"
    "../src/settings.cpp"
    )

target_link_libraries("test_settings"
    "boost_filesystem"
    )

target_link_libraries("test_run" "boost_unit_test_framework")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_target_properties("test_run" PROPERTIES
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
endif()
