project(aspire)

set(QML_SINGLETONS
)

set_source_files_properties(${QML_SINGLETONS}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION 1.0
    SOURCES
        FactoryComponent.cpp
        FactoryComponent.h
        ItemView.cpp
        ItemView.h
        ModelTreeItem.cpp
        ModelTreeItem.h
    QML_FILES
        ${QML_SINGLETONS}
    RESOURCES
    IMPORTS
        QtQuick
)

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/export.hxx BASE_NAME ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Quick
    Qt::QmlCompilerPrivate
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
