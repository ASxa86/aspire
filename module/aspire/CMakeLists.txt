project(aspire)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION 1.0
    SOURCES
        Aspire.cpp
        Aspire.h
        FrameMetrics.cpp
        FrameMetrics.h
        Meters.cpp
        Meters.h
    QML_FILES
        Counter.qml
        Square.qml
    IMPORTS
        QtQuick
)

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/export.hxx BASE_NAME ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Quick
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
