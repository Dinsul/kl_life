cmake_minimum_required(VERSION 3.2)

include_directories("${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/tests" ${CONAN_INCLUDE_DIRS})

link_libraries("${CONAN_LIBS}")

add_executable("test_run"
    "test_run.cpp"
    )

add_executable("test_settings"
    "test_settings.cpp"
    "../src/settings.cpp"
    )

add_executable("test_simpleuniverse"
    "test_simpleuniverse.cpp"
    "../src/simpleuniverse.cpp"
    "../src/universe.cpp"
    "../src/settings.cpp"
    "../src/logger.cpp"
    )


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_target_properties("test_run" PROPERTIES
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
endif()
