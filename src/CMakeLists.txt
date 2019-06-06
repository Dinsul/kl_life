cmake_minimum_required(VERSION 3.10)

include_directories("${PROJECT_SOURCE_DIR}/src" ${CONAN_INCLUDE_DIRS})

configure_file("${PROJECT_SOURCE_DIR}/info.h.in" "${PROJECT_SOURCE_DIR}/src/info.h")

add_executable("${PROJECT_NAME}"
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
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
    "${CONAN_LIBS}" "sfml-graphics" "sfml-window"
    )

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
