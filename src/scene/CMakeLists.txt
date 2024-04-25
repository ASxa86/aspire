project(aspire-scene)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/scene/Node.h
    Node.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
)

project_gen_export()
project_install_target()

add_subdirectory(test)