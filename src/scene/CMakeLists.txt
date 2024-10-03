project(aspire-scene)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/scene/Node.h
    ${PROJECT_INCLUDE_DIR}/aspire/scene/NodeGeometry.h
    ${PROJECT_INCLUDE_DIR}/aspire/scene/NodeTransform.h
)

target_sources(${PROJECT_NAME} PRIVATE
    Node.cpp
    NodeGeometry.cpp
    NodeTransform.cpp
)

find_package(glm CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
    aspire-core
    glm::glm
)

add_subdirectory(test)
