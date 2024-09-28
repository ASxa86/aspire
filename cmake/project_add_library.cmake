function(project_add_library)
    add_library(${ARGV})

    project_compile_lib()

    string(REPLACE "-" "/" LIBRARY_DIR ${PROJECT_NAME})
    generate_export_header(${PROJECT_NAME} BASE_NAME ${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/${LIBRARY_DIR}/export.hxx)

    if(BUILD_TESTING AND EXISTS test)
        add_subdirectory(test)
    endif()
endfunction()
