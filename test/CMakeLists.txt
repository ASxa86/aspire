project(test-aspire)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	Bitmask.test.cpp
	Node.test.cpp
	Window.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	aspire
	GTest::gtest_main
	GTest::gtest
)

project_install_target()
project_compile_options()
