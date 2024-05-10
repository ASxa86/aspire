project(aspire-core)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/core/Event.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Object.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Kernel.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Pimpl.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/PimplImpl.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Service.h
    Event.cpp
    Object.cpp
    Kernel.cpp
    Service.cpp
)

project_compile_options()
project_gen_export()
project_install_target()

add_subdirectory(test)