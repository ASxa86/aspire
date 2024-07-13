function(project_add_executable)
    qt_add_executable(${ARGV})
    project_compile_exe()
    project_install_target()

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
