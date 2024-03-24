cmake_minimum_required(VERSION 3.28)

include(${CMAKE_SOURCE_DIR}/cmake/compile_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/tidy.cmake)
include(FetchContent)

project(kiikku_survivors VERSION 0.1.0 LANGUAGES C)
set(NINJA_MULTICONFIG (CMAKE_GENERATOR STREQUAL "Ninja Multi-Config"))

fetch_project_dependencies()

set(PROJECT_SOURCES
    src/main.c
    src/viewport.c
    src/debug.c
    src/player.c
    src/input.c
    src/renderer.c
    src/enemy.c
    src/projectile.c
    src/game.c
    src/menus/main_menu.c
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 17)

add_project_compile_flags(${PROJECT_NAME})
link_project_dependencies(${PROJECT_NAME})

add_clang_tidy(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR})

if(NINJA_MULTICONFIG)
    foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOLOWER ${CONFIG} BUILD_NAME)
        add_custom_target(
            "run-${BUILD_NAME}"
            COMMAND
                ${CMAKE_COMMAND} -E env
                "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG}/${PROJECT_NAME}"
            USES_TERMINAL
            VERBATIM
            DEPENDS ${PROJECT_NAME}:$<CONFIG>
        )
    endforeach()
endif()
add_custom_target(
    run
    COMMAND ${CMAKE_COMMAND} -E env "$<TARGET_FILE:${PROJECT_NAME}>"
    USES_TERMINAL
    VERBATIM
    DEPENDS ${PROJECT_NAME}:$<CONFIG>
)

if(NINJA_MULTICONFIG)
    foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOLOWER ${CONFIG} CONFIG)
        add_custom_target(
            ${CONFIG}
            COMMAND
                ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}"
                "--config" "${CONFIG}"
            USES_TERMINAL
        )
    endforeach()
endif()
