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
        Counter.qml
        Square.qml
    IMPORTS
        QtQuick
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Quick
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
