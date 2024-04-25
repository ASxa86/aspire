project(aspire-render-test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Window.test.cpp
)

enable_testing()
    
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    GTest::gtest
    GTest::gtest_main
)

add_test(aspire-test ${PROJECT_NAME})

project_install_target()
