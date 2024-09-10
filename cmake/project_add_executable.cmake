function(project_add_executable target)
    add_executable(${target})

    project_compile_exe()

    install(TARGETS ${target}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    if(BUILD_TESTING AND EXISTS test)
        add_subdirectory(test)
    endif()

    # Make it possible to easily debug applications throug the visual studio debugger.
    if(MSVC)
        set(PROJECT_VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
        set(PROJECT_IMPORT_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/module ${PROJECT_VCPKG_ROOT}/Qt6/qml)
        set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${PROJECT_VCPKG_ROOT}/bin\nQML_IMPORT_PATH=${PROJECT_IMPORT_DIR}\nQT_PLUGIN_PATH=${PROJECT_VCPKG_ROOT}/Qt6/plugins")
    endif()
endfunction()
