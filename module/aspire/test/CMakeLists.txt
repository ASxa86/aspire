project(aspire-test)

add_executable(${PROJECT_NAME})

project_compile_exe()

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
    Meters.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::gtest
    aspire
)

gtest_discover_tests(${PROJECT_NAME}
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Testing
)
