project(aspire)

project_add_qml_module(
    SOURCES
        ${PROJECT_INCLUDE_DIR}/aspire/Aspire.h
        ${PROJECT_INCLUDE_DIR}/aspire/FrameMetrics.h
        ${PROJECT_INCLUDE_DIR}/aspire/Meters.h
        Aspire.cpp
        FrameMetrics.cpp
        Meters.cpp
    DEPENDENCIES
        QtQuick
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Quick
)

add_subdirectory(test)
