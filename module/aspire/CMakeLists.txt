project(aspire)

project_add_module(
    SOURCES
        Aspire.cpp
        Aspire.h
        FrameMetrics.cpp
        FrameMetrics.h
        Meters.cpp
        Meters.h
    QML_FILES
        Square.qml
    IMPORTS
        QtQuick
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Quick
)
