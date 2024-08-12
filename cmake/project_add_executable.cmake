function(project_add_executable target)
	string(REPLACE "-" "." MODULE_NAME ${target})

    qt_add_executable(${target} WIN32 MACOSX_BUNDLE)

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Main.qml)
        qt_add_qml_module(${target}
            URI ${MODULE_NAME}
            RESOURCE_PREFIX /
            QML_FILES
                Main.qml
        )
    endif()

    project_compile_exe()

    install(TARGETS ${target}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    qt_generate_deploy_qml_app_script(
        TARGET ${target}
        OUTPUT_SCRIPT deploy_script
        MACOS_BUNDLE_POST_BUILD
        NO_UNSUPPORTED_PLATFORM_ERROR
        DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
    )

    install(SCRIPT ${deploy_script})

    if(BUILD_TESTS AND EXISTS test)
        add_subdirectory(test)
    endif()

    # Make it possible to easily debug applications throug the visual studio debugger.
    if(MSVC)
        set(PROJECT_VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
        set(PROJECT_IMPORT_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/module ${PROJECT_VCPKG_ROOT}/Qt6/qml)
        set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${PROJECT_VCPKG_ROOT}/bin\nQML_IMPORT_PATH=${PROJECT_IMPORT_DIR}\nQT_PLUGIN_PATH=${PROJECT_VCPKG_ROOT}/Qt6/plugins")
    endif()
endfunction()
