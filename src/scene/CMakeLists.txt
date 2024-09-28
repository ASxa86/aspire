project(aspire-scene)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/scene/Node.h
)

target_sources(${PROJECT_NAME} PRIVATE
    Node.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    aspire-core
)

add_subdirectory(test)
