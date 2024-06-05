project(aspire-render)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/render/Event.h
    ${PROJECT_INCLUDE_DIR}/aspire/render/EventMouse.h
    ${PROJECT_INCLUDE_DIR}/aspire/render/EventWindow.h
    ${PROJECT_INCLUDE_DIR}/aspire/render/Window.h
    Window.cpp
)

find_package(SFML COMPONENTS graphics CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
)
