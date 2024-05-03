project(aspire)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    aspire-render
    aspire-scene
    aspire-widget
)

project_compile_options_exe()
project_install_target()
