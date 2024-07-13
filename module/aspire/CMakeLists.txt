project(aspire)

project_add_module(
    SOURCES
        Aspire.cpp
        Aspire.h
        FrameMetrics.cpp
        FrameMetrics.h
        Meters.cpp
        Meters.h
    DEPENDENCIES
        QtQuick
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Quick
)
