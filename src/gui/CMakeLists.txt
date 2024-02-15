project(aspire-gui)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}/aspire/gui/Context.h
    ${PROJECT_INCLUDE_DIR}/aspire/gui/EventMouse.h
    ${PROJECT_INCLUDE_DIR}/aspire/gui/Surface.h
    ${PROJECT_INCLUDE_DIR}/aspire/gui/Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
    Context.cpp
    ContextWin32.cpp
    ContextWin32.h
    EventMouse.cpp
    Window.cpp
)

if(MSVC)
    target_sources(${PROJECT_NAME} PRIVATE
        WindowWin32.cpp
    )    
elseif(UNIX)
    target_sources(${PROJECT_NAME} PRIVATE
        WindowX11.cpp
    )
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
	${OPENGL_gl_LIBRARY}
    aspire-core
    aspire-math
)

project_install_target()
project_gen_export()
