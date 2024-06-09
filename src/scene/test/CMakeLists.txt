project(aspire-scene-test)

project_add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Rectangle.test.cpp
    Window.test.cpp
)

enable_testing()
    
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    aspire-scene
    GTest::gtest_main
)

add_test(aspire-test ${PROJECT_NAME})
