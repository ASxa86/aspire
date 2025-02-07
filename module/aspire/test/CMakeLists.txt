project(aspire-test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
    WriteFileQML.test.cpp
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

# Make it possible to easily debug applications throug the visual studio debugger.
if(MSVC)
    set(PROJECT_VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>)
    set(PROJECT_IMPORT_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/module ${PROJECT_VCPKG_ROOT}/Qt6/qml)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${PROJECT_VCPKG_ROOT}/bin\nQML_IMPORT_PATH=${PROJECT_IMPORT_DIR}\nQT_PLUGIN_PATH=${PROJECT_VCPKG_ROOT}/Qt6/plugins")
endif()
