project(edhstats)

add_executable(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE MAIN_QML="${CMAKE_CURRENT_SOURCE_DIR}/main.qml")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    aspire
    Qt6::Quick
)

if(MSVC)
    set(VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${VCPKG_ROOT}/bin\nQT_PLUGIN_PATH=${VCPKG_ROOT}/Qt6/plugins\nQML_IMPORT_PATH=${VCPKG_ROOT}/Qt6/qml")
endif()