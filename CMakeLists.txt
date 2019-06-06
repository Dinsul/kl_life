cmake_minimum_required(VERSION 3.10)

project(life)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")

if ($ENV{TRAVIS_BUILD_NUMBER})
    set(PROJECT_VERSION_TWEAK $ENV{TRAVIS_BUILD_NUMBER})
else ()
    set(PROJECT_VERSION_TWEAK 0)
endif ()

set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                   "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include("${CMAKE_BINARY_DIR}/conan.cmake")

message(STATUS "Run 'conan install ...'")

conan_cmake_run(REQUIRES
    boost/1.69.0@conan/stable
    spdlog/1.2.1@bincrafters/stable
    sfml/2.5.0@bincrafters/stable

    OPTIONS
    boost:shared=False
    boost:without_wave=True
    boost:without_container=True
    boost:without_contract=True
    boost:without_exception=True
    boost:without_graph=True
    boost:without_iostreams=True
    boost:without_locale=True
    boost:without_log=True
    boost:without_program_options=True
    boost:without_random=True
    boost:without_regex=True
    boost:without_mpi=True
    boost:without_serialization=True
    boost:without_coroutine=True
    boost:without_fiber=True
    boost:without_context=True
    boost:without_thread=True
    boost:without_date_time=True
    boost:without_atomic=True
    boost:without_graph_parallel=True
    boost:without_python=True
    boost:without_stacktrace=True
    boost:without_type_erasure=True
    boost:without_chrono=True
    boost:without_timer=True
    boost:without_filesystem=True
    boost:without_math=True

    sfml:audio=False
    sfml:network=False

    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

cmake_policy(PUSH)
cmake_policy(SET CMP0057 NEW)

find_package(Doxygen)

set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_LATEX_MAKEINDEX_CMD YES)
set(DOXYGEN_PROJECT_LOGO "${CMAKE_SOURCE_DIR}/logo.png")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/doc")
set(DOXYGEN_OUTPUT_LANGUAGE "Russian")

doxygen_add_docs(doc "${PROJECT_SOURCE_DIR}")

cmake_policy(POP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_custom_target("sundries"
    SOURCES
    ".travis.yml"
    "info.h.in"
    "resources.rc.in"
    )

add_subdirectory("src")
add_subdirectory("tests")


add_test(test_all "test_run")
