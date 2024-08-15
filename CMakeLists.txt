cmake_minimum_required(VERSION 3.27)
enable_language(CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(cmake/project_compile_options.cmake)
include(cmake/project_add_library.cmake)
include(cmake/project_add_executable.cmake)
include(cmake/project_add_module.cmake)
include(cmake/project_gen_export.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/installed)

set(PROJECT_ROOT_NAME aspire)
project(${PROJECT_ROOT_NAME})

include(CTest)
include(GoogleTest)

option(BUILD_ENABLE_HARDENED "Enable hardened compiler options" OFF)
option(BUILD_TESTING "Enable building ${PROJECT_NAME} test applications." ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/module)
include_directories(${PROJECT_INCLUDE_DIR})

# Define build directory includes as system to avoid tools like clang-tidy from scanning them.
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR})

# Qt fails to find this path for android when it invokes Qt6AndroidMacros.cmake.
set(QT_ANDROID_PATH_CMAKE_DIR_${ANDROID_ABI} ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)

add_subdirectory(app)
add_subdirectory(module)

# set(PROJECT_CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ROOT_NAME}-config-version.cmake)
# write_basic_package_version_file(${PROJECT_CONFIG_VERSION} VERSION 0.0.0 COMPATIBILITY SameMajorVersion)

# install(EXPORT ${PROJECT_ROOT_NAME}-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
# install(DIRECTORY include/${PROJECT_ROOT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(FILES ${PROJECT_CONFIG_VERSION} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
