project(aspire-core)

project_add_library(${PROJECT_NAME})

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

add_subdirectory(test)
