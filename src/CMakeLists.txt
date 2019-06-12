cmake_minimum_required(VERSION 3.10)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
link_libraries(${CMAKE_THREAD_LIBS_INIT})

configure_file("${PROJECT_SOURCE_DIR}/info.h.in" "${PROJECT_SOURCE_DIR}/src/info.h")

add_executable("${PROJECT_NAME}"
    "${PROJECT_SOURCE_DIR}/src/life_types.hpp"
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/settings.cpp"
    "${PROJECT_SOURCE_DIR}/src/logger.cpp"
    "${PROJECT_SOURCE_DIR}/src/simpleuniverse.cpp"
    "${PROJECT_SOURCE_DIR}/src/universe.cpp"
    "${PROJECT_SOURCE_DIR}/src/game.cpp"
    )

#find_package(spdlog)
find_package(Boost REQUIRED COMPONENTS filesystem)

if(Boost_FOUND)
    target_include_directories("${PROJECT_NAME}" PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries("${PROJECT_NAME}" "${Boost_LIBRARIES}")
else()
    message("Boost not found!!!")
endif()

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

if(SFML_FOUND)
    target_include_directories("${PROJECT_NAME}" PUBLIC ${SFML_INCLUDE_DIR})
    target_link_libraries("${PROJECT_NAME}" "sfml-system" "sfml-graphics" "sfml-window" "-lpthread")
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

include_directories("${PROJECT_SOURCE_DIR}/src" "${Boost_INCLUDE_DIRS}")

if (WIN32)
    configure_file("${PROJECT_SOURCE_DIR}/resources.rc.in" "${PROJECT_SOURCE_DIR}/src/resources.rc")

    target_sources("${PROJECT_NAME}" PUBLIC "${PROJECT_SOURCE_DIR}/src/resources.rc")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR DEB)
    message("Package for linux generated as DEB")
endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_TWEAK "${PROJECT_VERSION_TWEAK}")

set(CPACK_PACKAGE_CONTACT dinsul2.0@gmail.com)

include (CPack)
