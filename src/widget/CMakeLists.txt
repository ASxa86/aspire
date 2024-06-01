project(aspire-widget)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/widget/Widget.h
    ${PROJECT_INCLUDE_DIR}/aspire/widget/Window.h
    Widget.cpp
    Window.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    aspire-scene
    aspire-render
)

add_subdirectory(test)
