project(aspire)

add_library(${PROJECT_NAME})

set(CORE_H
	${PROJECT_INCLUDE_DIR}/aspire/core/Event.h
	${PROJECT_INCLUDE_DIR}/aspire/core/Kernel.h
	${PROJECT_INCLUDE_DIR}/aspire/core/Object.h
	${PROJECT_INCLUDE_DIR}/aspire/core/Pimpl.h
	${PROJECT_INCLUDE_DIR}/aspire/core/PimplImpl.h
	${PROJECT_INCLUDE_DIR}/aspire/core/Signal.h
	${PROJECT_INCLUDE_DIR}/aspire/core/Slot.h
)

set(CORE_SRC
	core/Event.cpp
	core/Kernel.cpp
	core/Object.cpp
	core/Signal.cpp
	core/Slot.cpp
)

set(GUI_H
	${PROJECT_INCLUDE_DIR}/aspire/gui/Context.h
	${PROJECT_INCLUDE_DIR}/aspire/gui/EventMouse.h
	${PROJECT_INCLUDE_DIR}/aspire/gui/Surface.h
	${PROJECT_INCLUDE_DIR}/aspire/gui/Window.h
)

set(GUI_SRC
	gui/Context.cpp
	gui/EventMouse.cpp
	gui/Window.cpp
)

set(MATH_H
	${PROJECT_INCLUDE_DIR}/aspire/math/Point.h
)

set(MATH_SRC
	math/Point.cpp
)

if(WIN32)
	list(APPEND GUI_SRC
        gui/WindowWin32.cpp
        gui/ContextWin32.h
		gui/ContextWin32.cpp
     )
elseif(UNIX)
	list(APPEND GUI_SRC
		gui/WindowX11.cpp
	)
endif()

target_sources(${PROJECT_NAME} PRIVATE
	${CORE_H}
	${GUI_H}
	${MATH_H}
)

target_sources(${PROJECT_NAME} PRIVATE
	${CORE_SRC}
	${GUI_SRC}
	${MATH_SRC}
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
	${OPENGL_gl_LIBRARY}
)

source_group("include/core" FILES ${CORE_H})
source_group("src/core" FILES ${CORE_SRC})
source_group("include/gui" FILES ${GUI_H})
source_group("src/gui" FILES ${GUI_SRC})
source_group("include/math" FILES ${MATH_H})
source_group("src/math" FILES ${MATH_SRC})

project_install_target()
project_gen_export()
