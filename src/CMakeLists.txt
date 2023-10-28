project(aspire)

project_add_qml_module(
    SOURCES
        ${PROJECT_INCLUDE_DIR}/aspire/FrameMetrics.h
        FrameMetrics.cpp
    DEPENDENCIES
        QtQuick
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
)

project_gen_export()
project_install_target()
