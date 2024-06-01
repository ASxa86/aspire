project(aspire-scene)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/scene/Node.h
    Node.cpp
)

add_subdirectory(test)
