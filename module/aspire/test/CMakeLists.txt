project(aspire-test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
    ParseQmlTypes.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::gtest
    aspire
)

if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL Android)
    gtest_discover_tests(${PROJECT_NAME}
        XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Testing
    )
endif()
