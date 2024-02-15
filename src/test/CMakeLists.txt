project(aspire-test)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/test/Test.h
)

target_sources(${PROJECT_NAME} PRIVATE
    Test.cpp
)

project_install_target()
project_gen_export()
