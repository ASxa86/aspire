project(aspire-edit)

qt_add_executable(${PROJECT_NAME})

# For static builds.
qt_import_qml_plugins(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Quick
)

project_install_target()

if(WIN32)
    set(PROJECT_VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${PROJECT_VCPKG_ROOT}/bin\nQML_IMPORT_PATH=${PROJECT_VCPKG_ROOT}/Qt6/qml\nQT_PLUGIN_PATH=${PROJECT_VCPKG_ROOT}/Qt6/plugins")
endif()
