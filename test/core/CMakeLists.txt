project(test-aspire-core)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Signal.test.cpp
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    aspire-test
)

project_install_target()
