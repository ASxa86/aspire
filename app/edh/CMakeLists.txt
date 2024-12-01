project(edh)

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
    main.cpp
)

set(QML_SINGLETONS
    Actions.qml
    Style.qml 
)

set_source_files_properties(${QML_SINGLETONS}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(${PROJECT_NAME}
    URI app.${PROJECT_NAME}
    VERSION 1.0
    QML_FILES
        Counter.qml
        IconLayout.qml
        Main.qml
        MenuEDH.qml
        MenuLife.qml
        ModelPlayers.qml
        TextEDH.qml
        ${QML_SINGLETONS}
    IMPORTS
        aspire
    IMPORT_PATH
        ${CMAKE_BINARY_DIR}/module
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Quick
)

# Link against plugins for static builds.
if(${CMAKE_SYSTEM_NAME} STREQUAL Darwin OR ${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        aspireplugin
    )
endif()

# Android APKs are handle separately within Qt cmake scripts.
if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL Android)
    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    qt_generate_deploy_qml_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT deploy_script
        MACOS_BUNDLE_POST_BUILD
        NO_UNSUPPORTED_PLATFORM_ERROR
        DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
    )

    install(SCRIPT ${deploy_script})
endif()

# Make it possible to easily debug applications throug the visual studio debugger.
if(MSVC)
    set(PROJECT_VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>)
    set(PROJECT_IMPORT_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/module ${PROJECT_VCPKG_ROOT}/Qt6/qml)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${PROJECT_VCPKG_ROOT}/bin\nQML_IMPORT_PATH=${PROJECT_IMPORT_DIR}\nQT_PLUGIN_PATH=${PROJECT_VCPKG_ROOT}/Qt6/plugins")
endif()
