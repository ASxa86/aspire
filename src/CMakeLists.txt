add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(math)
add_subdirectory(test)

project_add_qml_module(
    SOURCES
        ${PROJECT_INCLUDE_DIR}/aspire/Entity.h
        ${PROJECT_INCLUDE_DIR}/aspire/FrameMetrics.h
        ${PROJECT_INCLUDE_DIR}/aspire/ModelEntity.h
        Entity.cpp
        FrameMetrics.cpp
        ModelEntity.cpp
    DEPENDENCIES
        QtQuick
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
)

project_gen_export()
project_install_target()
