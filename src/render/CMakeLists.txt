project(aspire-render)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/render/Event.h
    ${PROJECT_INCLUDE_DIR}/aspire/render/EventMouse.h
    ${PROJECT_INCLUDE_DIR}/aspire/render/EventWindow.h
    ${PROJECT_INCLUDE_DIR}/aspire/render/Window.h
    Window.cpp
)

find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
)
