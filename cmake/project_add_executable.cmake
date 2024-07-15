function(project_add_executable)
    if(APPLE)
        set(PROJECT_PLATFORM MACOSX_BUNDLE)
    endif()

	string(REPLACE "-" "." MODULE_NAME ${PROJECT_NAME})

    qt_add_executable(${PROJECT_NAME} ${PROJECT_PLATFORM})
    qt_add_qml_module(${PROJECT_NAME}
        URI qml.${PROJECT_NAME}
        VERSION 1.0
        RESOURCE_PREFIX /
        ${ARGV}
    )

    project_compile_exe()

    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    qt_generate_deploy_qml_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT deploy_script
        MACOS_BUNDLE_POST_BUILD
    )

    install(SCRIPT ${deploy_script})

    if(BUILD_TESTS AND EXISTS test)
        add_subdirectory(test)
    endif()

    # For static builds.
    qt_import_qml_plugins(${PROJECT_NAME})

    if(MSVC)
        if("${VCPKG_BUILD_TYPE}" STREQUAL "release")
            set(PROJECT_VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
        else()
            set(PROJECT_VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>)
        endif()

        set(PROJECT_IMPORT_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/module ${PROJECT_VCPKG_ROOT}/Qt6/qml)
        set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${PROJECT_VCPKG_ROOT}/bin\nQML_IMPORT_PATH=${PROJECT_IMPORT_DIR}\nQT_PLUGIN_PATH=${PROJECT_VCPKG_ROOT}/Qt6/plugins")
    endif()
endfunction()
