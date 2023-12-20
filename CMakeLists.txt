cmake_minimum_required(VERSION 3.22)
enable_language(CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(cmake/project_add_qml_module.cmake)
include(cmake/project_install_target.cmake)
include(cmake/project_gen_export.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(PROJECT_ROOT_NAME aspire)
project(${PROJECT_ROOT_NAME})

option(BUILD_SHARED_LIBS "Enable building ${PROJECT_NAME} as shared libraries." ON)
option(BUILD_TESTS "Enable building ${PROJECT_NAME} test applications." ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add_subdirectory(app)
add_subdirectory(src)

set(PROJECT_CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ROOT_NAME}-config-version.cmake)
write_basic_package_version_file(${PROJECT_CONFIG_VERSION} VERSION 0.0.0 COMPATIBILITY SameMajorVersion)

install(EXPORT ${PROJECT_ROOT_NAME}-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
install(DIRECTORY include/${PROJECT_ROOT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${PROJECT_CONFIG_VERSION} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
