project(aspire-scene)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/scene/Node.h
    ${PROJECT_INCLUDE_DIR}/aspire/scene/Window.h  
)

target_sources(${PROJECT_NAME} PRIVATE
    Node.cpp
    Window.cpp
)

find_package(SFML COMPONENTS graphics CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    sfml-graphics
)

add_subdirectory(test)
