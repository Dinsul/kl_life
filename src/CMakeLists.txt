cmake_minimum_required(VERSION 3.10)

include_directories("${PROJECT_SOURCE_DIR}/src"
    ${CONAN_INCLUDE_DIRS}
    "${PROJECT_SOURCE_DIR}/SFML-2.5.1/include")

link_directories(${CONAN_LIB_DIRS} "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib")

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


target_link_libraries(${PROJECT_NAME}
    "${CONAN_LIBS}" "sfml-system" "sfml-graphics" "sfml-window"
    )


if (WIN32)
    configure_file("${PROJECT_SOURCE_DIR}/resources.rc.in" "${PROJECT_SOURCE_DIR}/src/resources.rc")

    target_sources("${PROJECT_NAME}" PUBLIC "${PROJECT_SOURCE_DIR}/src/resources.rc")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
endif()


target_link_libraries(${PROJECT_NAME}
    "${CONAN_LIBS}" "sfml-system" "sfml-graphics" "sfml-window"
    )


install(TARGETS "${PROJECT_NAME}"
    RUNTIME
    DESTINATION bin)

#install(TARGETS
#    "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-graphics.so.2.5.1"
#    "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-system.so.2.5.1"
#    "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-window.so.2.5.1"

#    LIBRARY
#    DESTINATION lib
#    COMPONENT Libraries)

install(FILES
    "${PROJECT_SOURCE_DIR}/data/Casatus.ttf"
    DESTINATION "${FONTS_DIR}"
    COMPONENT Data)

#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsfml-dev (>= 2.4.0)")

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
