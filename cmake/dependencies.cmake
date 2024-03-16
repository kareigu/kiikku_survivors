function(fetch_project_dependencies)
    fetchcontent_declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG 5.0
        GIT_PROGRESS TRUE
        USES_TERMINAL_DOWNLOAD
        TRUE
        SYSTEM
    )
    fetchcontent_makeavailable(raylib)
endfunction()

function(link_project_dependencies PROJECT_NAME)
    target_link_libraries(${PROJECT_NAME} raylib)
endfunction()
