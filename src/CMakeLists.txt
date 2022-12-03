project(aspire)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/aspire/BufferObject.h
	${PROJECT_INCLUDE_DIR}/aspire/BufferObjectVertex.h
	${PROJECT_INCLUDE_DIR}/aspire/Bitmask.h
	${PROJECT_INCLUDE_DIR}/aspire/Camera.h
	${PROJECT_INCLUDE_DIR}/aspire/Event.h
	${PROJECT_INCLUDE_DIR}/aspire/Node.h
	${PROJECT_INCLUDE_DIR}/aspire/NodeGeometry.h
	${PROJECT_INCLUDE_DIR}/aspire/Primitive.h
	${PROJECT_INCLUDE_DIR}/aspire/PrimitiveDrawArrays.h
	${PROJECT_INCLUDE_DIR}/aspire/Program.h
	${PROJECT_INCLUDE_DIR}/aspire/Shader.h
	${PROJECT_INCLUDE_DIR}/aspire/Vertex.h
	${PROJECT_INCLUDE_DIR}/aspire/Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	BufferObject.cpp
	BufferObjectVertex.cpp
	Camera.cpp
	Node.cpp
	NodeGeometry.cpp
	Primitive.cpp
	PrimitiveDrawArrays.cpp
	Program.cpp
	Shader.cpp
	Window.cpp
)

find_package(ZLIB REQUIRED)
find_package(unofficial-angle CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Find X11 dependencies for angle which includes these targets with its own.
if(UNIX)
	find_package(X11 REQUIRED)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
	glfw
	glm::glm
	unofficial::angle::libEGL
	unofficial::angle::libANGLE
	unofficial::angle::libGLESv2
	unofficial::angle::angle_common
)

project_install_target()
project_compile_options()
project_gen_export()
