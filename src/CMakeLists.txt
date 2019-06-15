cmake_minimum_required(VERSION 3.10)

find_package(SFML)

if (NOT SFML_FOUND)

    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML/SFMLConfig.cmake")

        if(UNIX)
            message(STATUS "Downloading SFML")

            if (APPLE)
                file(DOWNLOAD "https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz"
                    "${PROJECT_SOURCE_DIR}/SFML-2.5.1-macOS-clang.tar.gz")
            else()
                file(DOWNLOAD "https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz"
                    "${PROJECT_SOURCE_DIR}/SFML-2.5.1-linux-gcc-64-bit.tar.gz")
            endif()

            execute_process(COMMAND tar xvzf SFML-2.5.1-linux-gcc-64-bit.tar.gz SFML-2.5.1
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

            execute_process(COMMAND rm SFML-2.5.1-linux-gcc-64-bit.tar.gz
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
        endif()
    endif()

    set (SFML_DIR "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")

    find_package(SFML COMPONENTS graphics window system)

    link_directories("${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib")
    include_directories("${PROJECT_SOURCE_DIR}/SFML-2.5.1/include")

endif()

link_directories(${CONAN_LIB_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/src" "${CONAN_INCLUDE_DIRS}")

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

install(FILES
    "${PROJECT_SOURCE_DIR}/data/Casatus.ttf"
    "${PROJECT_SOURCE_DIR}/data/lset.png"
    DESTINATION "${PRJ_INSTALL_DIR}"
    COMPONENT Data)

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsfml-dev (>= 2.4)")

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR DEB)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_TWEAK "${PROJECT_VERSION_TWEAK}")

set(CPACK_PACKAGE_CONTACT dinsul2.0@gmail.com)

include (CPack)
