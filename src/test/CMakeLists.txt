project(aspire-test)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/test/Kernel.h
    ${PROJECT_INCLUDE_DIR}/aspire/test/Test.h
    ${PROJECT_INCLUDE_DIR}/aspire/test/Unit.h
)

target_sources(${PROJECT_NAME} PRIVATE
    Kernel.cpp
    Test.cpp
    Unit.cpp
)

project_install_target()
project_gen_export()
