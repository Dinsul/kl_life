cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

find_package(Boost REQUIRED COMPONENTS unit_test_framework filesystem system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_libraries("${Boost_LIBRARIES}")
else()
    message("Boost not found!!!")
endif()

include_directories("${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/tests")


add_executable("test_run"
    "test_run.cpp"
    )

#add_executable("test_settings"
#    "test_settings.cpp"
#    "../src/settings.cpp"
#    )

#add_executable("test_simpleuniverse"
#    "test_simpleuniverse.cpp"
#    "../src/simpleuniverse.cpp"
#    "../src/universe.cpp"
#    "../src/settings.cpp"
#    "../src/logger.cpp"
#    )

#target_link_libraries("test_simpleuniverse" "pthread")


target_link_libraries("test_run" "boost_unit_test_framework")
#target_link_libraries("test_settings" "boost_unit_test_framework")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_target_properties("test_run" PROPERTIES
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
endif()
