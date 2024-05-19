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