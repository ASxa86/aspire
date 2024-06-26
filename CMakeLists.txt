cmake_minimum_required(VERSION 3.27)
enable_language(CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(cmake/project_compile_options.cmake)
include(cmake/project_add_library.cmake)
include(cmake/project_add_executable.cmake)
include(cmake/project_gen_export.cmake)
include(cmake/project_install_target.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/RelWithDebInfo")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/RelWithDebInfo")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/RelWithDebInfo")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 23)

set(PROJECT_ROOT_NAME aspire)
project(${PROJECT_ROOT_NAME})

option(BUILD_SHARED_LIBS "Enable building ${PROJECT_NAME} as shared libraries." ON)
option(BUILD_ENABLE_HARDENED "Enable hardened compiler options" OFF)
option(BUILD_TESTS "Enable building ${PROJECT_NAME} test applications." OFF)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_INCLUDE_DIR})

# Define build directory includes as system to avoid tools like clang-tidy from scanning them.
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(app)
add_subdirectory(src)

set(PROJECT_CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ROOT_NAME}-config-version.cmake)
write_basic_package_version_file(${PROJECT_CONFIG_VERSION} VERSION 0.0.0 COMPATIBILITY SameMajorVersion)

install(EXPORT ${PROJECT_ROOT_NAME}-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
install(DIRECTORY include/${PROJECT_ROOT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${PROJECT_CONFIG_VERSION} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
