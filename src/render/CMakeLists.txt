project(aspire-render)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/render/Window.h
    Window.cpp
)

project_gen_export()
project_install_target()

add_subdirectory(test)