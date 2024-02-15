project(aspire-math)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/math/Point.h
)

target_sources(${PROJECT_NAME} PRIVATE
    Point.cpp
)

project_install_target()
project_gen_export()
