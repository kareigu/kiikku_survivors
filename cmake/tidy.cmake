#
# clang-tidy
#
function(add_clang_tidy PROJECT_NAME CURRENT_DIR)
    find_program(
        CLANG_TIDY
        clang-tidy
        NO_CACHE
        DOC "clang-tidy is required for the static analysis stage"
    )
    if(CLANG_TIDY)
        file(GLOB_RECURSE CLANG_TIDY_SOURCES src/*.c src/*.h)
        add_custom_target(
            tidy
            COMMAND
                ${CMAKE_COMMAND} -E env "${CLANG_TIDY}" "-p" "${CURRENT_DIR}"
                ${CLANG_TIDY_SOURCES}
            USES_TERMINAL
            DEPENDS ${PROJECT_NAME}
        )
    endif()
endfunction()
#
# end: clang-tidy
#
