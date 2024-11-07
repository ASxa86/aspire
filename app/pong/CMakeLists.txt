project(pong)

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
    main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI app.${PROJECT_NAME}
    VERSION 1.0
    QML_FILES
        Main.qml
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Quick
)

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
