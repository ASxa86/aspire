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
