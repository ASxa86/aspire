project(aspire)

project_add_qml_module(
    SOURCES
        ${PROJECT_INCLUDE_DIR}/aspire/Aspire.h
        ${PROJECT_INCLUDE_DIR}/aspire/FrameMetrics.h
        Aspire.cpp
        FrameMetrics.cpp
    DEPENDENCIES
        QtQuick
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Quick
)
