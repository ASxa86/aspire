function(project_add_library)
    qt_add_library(${ARGV})
    project_compile_lib()

    if(BUILD_TESTS AND EXISTS test)
        add_subdirectory(test)
    endif()
endfunction()
