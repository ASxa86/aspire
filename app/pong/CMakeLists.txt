project(pong)

project_add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Ball.cpp
    Ball.h
    main.cpp
    Menu.cpp
    Menu.h
    Paddle.cpp
    Paddle.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    aspire-widget
)
