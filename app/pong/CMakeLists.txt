project(aspire-pong)

project_add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Ball.cpp
    Ball.h
    main.cpp
    Paddle.cpp
    Paddle.h
    Player.cpp
    Player.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-scene
)
