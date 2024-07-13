function(project_add_executable)
    if(APPLE)
        set(PROJECT_PLATFORM MACOSX_BUNDLE)
    endif()
    qt_add_executable(${ARGV} ${PROJECT_PLATFORM})
    project_compile_exe()

    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    qt_generate_deploy_qml_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT target_install
        MACOS_BUNDLE_POST_BUILD
    )

    message(STATUS "SCRIPT: ${target_install}")
    install(SCRIPT ${target_install})

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

        set(PROJECT_IMPORT_DIR ${CMAKE_BINARY_DIR}/module ${PROJECT_VCPKG_ROOT}/Qt6/qml)
        set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${PROJECT_VCPKG_ROOT}/bin\nQML_IMPORT_PATH=${PROJECT_IMPORT_DIR}\nQT_PLUGIN_PATH=${PROJECT_VCPKG_ROOT}/Qt6/plugins")
    endif()
endfunction()
