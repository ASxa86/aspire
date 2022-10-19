project(aspire)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/aspire/Node.h
	${PROJECT_INCLUDE_DIR}/aspire/Visitor.h
	${PROJECT_INCLUDE_DIR}/aspire/VisitorCollect.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Node.cpp
	Visitor.cpp
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
	glfw
	glad::glad
	glm::glm
)

project_install_target()
project_compile_options()
project_gen_export()
