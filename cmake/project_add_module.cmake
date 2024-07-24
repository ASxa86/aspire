function(project_add_module)
    # Define URI and folder path.
    string(REPLACE "-" "/" MODULE_FOLDER_NAME ${PROJECT_NAME})
    string(REPLACE "-" "." MODULE_URI_NAME ${PROJECT_NAME})

    if(NOT TARGET ${PROJECT_NAME})
        if(BUILD_SHARED_LIBS)
            set(PROJECT_QML_LINKAGE SHARED)
        else()
            set(PROJECT_QML_LINKAGE STATIC)
        endif()
    endif()

    qt_add_qml_module(${PROJECT_NAME}
        URI ${MODULE_URI_NAME}
        VERSION 1.0
        RESOURCE_PREFIX /
        ${PROJECT_QML_LINKAGE}
        ${ARGV}
    )

    target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR}/${MODULE_FOLDER_NAME})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    project_gen_export()

    if(BUILD_TESTS AND EXISTS test)
        add_subdirectory(test)
    endif()
endfunction()
