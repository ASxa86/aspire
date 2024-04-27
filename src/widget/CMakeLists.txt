project(aspire-widget)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/widget/Widget.h
    ${PROJECT_INCLUDE_DIR}/aspire/widget/Window.h
    Widget.cpp
    Window.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    aspire-scene
)

project_gen_export()
project_install_target()

add_subdirectory(test)
