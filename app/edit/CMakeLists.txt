project(aspire-edit)

project_add_executable(
    QML_FILES
        Main.qml
    IMPORTS
        aspire
)

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Quick
)
