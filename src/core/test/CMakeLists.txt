project(aspire-core-test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Object.test.cpp
)

enable_testing()
    
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire-core
    GTest::gtest
    GTest::gtest_main
)

add_test(aspire-test ${PROJECT_NAME})

project_compile_options()
project_install_target()
