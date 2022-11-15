project(aspire)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/aspire/Bitmask.h
	${PROJECT_INCLUDE_DIR}/aspire/Camera.h
	${PROJECT_INCLUDE_DIR}/aspire/Event.h
	${PROJECT_INCLUDE_DIR}/aspire/Node.h
	${PROJECT_INCLUDE_DIR}/aspire/NodeGeometry.h
	${PROJECT_INCLUDE_DIR}/aspire/Primitive.h
	${PROJECT_INCLUDE_DIR}/aspire/PrimitiveDrawArrays.h
	${PROJECT_INCLUDE_DIR}/aspire/Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Camera.cpp
	Node.cpp
	NodeGeometry.cpp
	Primitive.cpp
	PrimitiveDrawArrays.cpp
	Window.cpp
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
