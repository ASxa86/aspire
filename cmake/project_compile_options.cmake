function(project_compile_options)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE
            /wd4251
        )
    endif()
endfunction()

function(project_compile_options_exe)
    project_compile_options()

    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
endfunction()