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

    if(MSVC)
        set(PROJECT_MODULE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/${MODULE_FOLDER_NAME})
    else()
        set(PROJECT_MODULE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MODULE_FOLDER_NAME})
    endif()

    target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR}/${MODULE_FOLDER_NAME})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    # Collect all *.qml files from the project and ensure they're installed to the project's plugin directory.
    # file(GLOB QML_FILES ${QML_OUTPUT_DIRECTORY}/*.qml)

    # list(APPEND QML_FILES ${QML_OUTPUT_DIRECTORY}/qmldir ${QML_OUTPUT_DIRECTORY}/${PROJECT_NAME}.qmltypes)

    # install(
    #     FILES ${QML_FILES}
    #     DESTINATION ${CMAKE_INSTALL_PREFIX}/qml/${MODULE_FOLDER_NAME}
    # )

    # install(
    #     TARGETS ${PROJECT_NAME}-plugin
    #     EXPORT ${PROJECT_EXPORT_TARGET}
    #     LIBRARY DESTINATION plugins/${MODULE_FOLDER_NAME}
    #     ARCHIVE DESTINATION plugins/${MODULE_FOLDER_NAME}
    #     RUNTIME DESTINATION plugins/${MODULE_FOLDER_NAME}
    # )

    project_gen_export()
    # project_install_target()

    if(BUILD_TESTS AND EXISTS test)
        add_subdirectory(test)
    endif()
endfunction()
