project(aspire-widget-test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Widget.test.cpp
    Window.test.cpp
)

enable_testing()
    
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-widget
    GTest::gtest_main
)

add_test(aspire-test ${PROJECT_NAME})

project_compile_options_exe()
project_install_target()
