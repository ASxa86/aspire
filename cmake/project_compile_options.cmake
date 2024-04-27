function(project_compile_options)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE
            /wd4251
        )
    endif()
endfunction()