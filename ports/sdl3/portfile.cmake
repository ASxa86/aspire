vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO libsdl-org/SDL
    REF main
    SHA512 91ed84d834c886290b55a4f40b88f09b7adf6c237b7e5e95bd6ae04725a8bff1f824438291996cf5788ebe3e85db16f4ce6ca0adbc78fb25fcfef2366da52abe
    HEAD_REF main
    # PATCHES
        # deps.patch
        # alsa-dep-fix.patch
        # cxx-linkage-pkgconfig.diff
)

string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "static" SDL_STATIC)
string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "dynamic" SDL_SHARED)
string(COMPARE EQUAL "${VCPKG_CRT_LINKAGE}" "static" FORCE_STATIC_VCRT)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        alsa     SDL_ALSA
        dbus     SDL_DBUS
        ibus     SDL_IBUS
        samplerate SDL_LIBSAMPLERATE
        vulkan   SDL_VULKAN
        wayland  SDL_WAYLAND
        x11      SDL_X11
)

if ("x11" IN_LIST FEATURES)
    message(WARNING "You will need to install Xorg dependencies to use feature x11:\nsudo apt install libx11-dev libxft-dev libxext-dev\n")
endif()
if ("wayland" IN_LIST FEATURES)
    message(WARNING "You will need to install Wayland dependencies to use feature wayland:\nsudo apt install libwayland-dev libxkbcommon-dev libegl1-mesa-dev\n")
endif()
if ("ibus" IN_LIST FEATURES)
    message(WARNING "You will need to install ibus dependencies to use feature ibus:\nsudo apt install libibus-1.0-dev\n")
endif()

if(VCPKG_TARGET_IS_UWP)
    set(configure_opts WINDOWS_USE_MSBUILD)
endif()

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    ${configure_opts}
    OPTIONS ${FEATURE_OPTIONS}
        -DSDL_STATIC=${SDL_STATIC}
        -DSDL_SHARED=${SDL_SHARED}
        -DSDL_FORCE_STATIC_VCRT=${FORCE_STATIC_VCRT}
        -DSDL_LIBC=ON
        -DSDL_TEST=OFF
        -DSDL_INSTALL_CMAKEDIR=cmake
        -DCMAKE_DISABLE_FIND_PACKAGE_Git=ON
        -DSDL_LIBSAMPLERATE_SHARED=OFF
    MAYBE_UNUSED_VARIABLES
        SDL_FORCE_STATIC_VCRT
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH cmake)

file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/debug/include"
    "${CURRENT_PACKAGES_DIR}/debug/share"
    "${CURRENT_PACKAGES_DIR}/bin/sdl3-config"
    "${CURRENT_PACKAGES_DIR}/debug/bin/sdl3-config"
    "${CURRENT_PACKAGES_DIR}/SDL3.framework"
    "${CURRENT_PACKAGES_DIR}/debug/SDL3.framework"
    "${CURRENT_PACKAGES_DIR}/share/licenses"
    "${CURRENT_PACKAGES_DIR}/share/aclocal"
)

file(GLOB BINS "${CURRENT_PACKAGES_DIR}/debug/bin/*" "${CURRENT_PACKAGES_DIR}/bin/*")
if(NOT BINS)
    file(REMOVE_RECURSE
        "${CURRENT_PACKAGES_DIR}/bin"
        "${CURRENT_PACKAGES_DIR}/debug/bin"
    )
endif()

if(VCPKG_TARGET_IS_WINDOWS AND NOT VCPKG_TARGET_IS_UWP AND NOT VCPKG_TARGET_IS_MINGW)
    if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "release")
        file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/lib/manual-link")
        # file(RENAME "${CURRENT_PACKAGES_DIR}/lib/SDL3main.lib" "${CURRENT_PACKAGES_DIR}/lib/manual-link/SDL3main.lib")
    endif()
    if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "debug")
        file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/debug/lib/manual-link")
        # file(RENAME "${CURRENT_PACKAGES_DIR}/debug/lib/SDL3maind.lib" "${CURRENT_PACKAGES_DIR}/debug/lib/manual-link/SDL3maind.lib")
    endif()

    file(GLOB SHARE_FILES "${CURRENT_PACKAGES_DIR}/share/sdl3/*.cmake")
    foreach(SHARE_FILE ${SHARE_FILES})
        # vcpkg_replace_string("${SHARE_FILE}" "lib/SDL3main" "lib/manual-link/SDL3main" IGNORE_UNCHANGED)
    endforeach()
endif()

vcpkg_copy_pdbs()

set(DYLIB_COMPATIBILITY_VERSION_REGEX "set\\(DYLIB_COMPATIBILITY_VERSION (.+)\\)")
set(DYLIB_CURRENT_VERSION_REGEX "set\\(DYLIB_CURRENT_VERSION (.+)\\)")
file(STRINGS "${SOURCE_PATH}/CMakeLists.txt" DYLIB_COMPATIBILITY_VERSION REGEX ${DYLIB_COMPATIBILITY_VERSION_REGEX})
file(STRINGS "${SOURCE_PATH}/CMakeLists.txt" DYLIB_CURRENT_VERSION REGEX ${DYLIB_CURRENT_VERSION_REGEX})
string(REGEX REPLACE ${DYLIB_COMPATIBILITY_VERSION_REGEX} "\\1" DYLIB_COMPATIBILITY_VERSION "${DYLIB_COMPATIBILITY_VERSION}")
string(REGEX REPLACE ${DYLIB_CURRENT_VERSION_REGEX} "\\1" DYLIB_CURRENT_VERSION "${DYLIB_CURRENT_VERSION}")

if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "debug" AND NOT VCPKG_TARGET_IS_ANDROID)
    # vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/sdl3.pc" "-lSDL3main" "-lSDL3maind" IGNORE_UNCHANGED)
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/sdl3.pc" "-lSDL3 " "-lSDL3d " IGNORE_UNCHANGED)
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/sdl3.pc" "-lSDL3-static " "-lSDL3-staticd " IGNORE_UNCHANGED)
endif()

if(VCPKG_LIBRARY_LINKAGE STREQUAL "dynamic" AND VCPKG_TARGET_IS_WINDOWS AND NOT VCPKG_TARGET_IS_MINGW)
    if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "release")
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/lib/pkgconfig/sdl3.pc" "-lSDL3-static " " ")
    endif()
    if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "debug")
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/sdl3.pc" "-lSDL3-staticd " " ")
    endif()
endif()

if(VCPKG_TARGET_IS_UWP)
    if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "release")
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/lib/pkgconfig/sdl3.pc" "$<$<CONFIG:Debug>:d>.lib" "")
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/lib/pkgconfig/sdl3.pc" "-l-nodefaultlib:" "-nodefaultlib:")
    endif()
    if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "debug")
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/sdl3.pc" "$<$<CONFIG:Debug>:d>.lib" "d")
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/sdl3.pc" "-l-nodefaultlib:" "-nodefaultlib:")
    endif()
endif()

vcpkg_fixup_pkgconfig()

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE.txt")