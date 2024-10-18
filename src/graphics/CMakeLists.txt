project(aspire-graphics)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/graphics/Color.h
    ${PROJECT_INCLUDE_DIR}/aspire/graphics/Event.h
    ${PROJECT_INCLUDE_DIR}/aspire/graphics/Window.h
    Window.cpp
)

find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
)
