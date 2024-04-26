project(aspire-core)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/core/Object.h
    Object.cpp
)

project_gen_export()
project_install_target()

add_subdirectory(test)