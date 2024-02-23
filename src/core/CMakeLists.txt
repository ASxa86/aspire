project(aspire-core)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/core/Event.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/EventTimer.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Kernel.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Object.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Pimpl.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/PimplImpl.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Signal.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Slot.h
    ${PROJECT_INCLUDE_DIR}/aspire/core/Timer.h
)

target_sources(${PROJECT_NAME} PRIVATE
    Event.cpp
    EventTimer.cpp
    Kernel.cpp
    Object.cpp
    Signal.cpp
    Slot.cpp
    Timer.cpp
)

project_install_target()
project_gen_export()
