project(shapes)

add_executable(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE MAIN_QML="${CMAKE_CURRENT_SOURCE_DIR}/main.qml")

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Quick)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire
    Qt6::Quick
)