# These ports were not playing nice when compiling as dynamic.
set(STATIC_PORTS
    harfbuzz
    libb2
)

if(PORT IN_LIST STATIC_PORTS)
    set(VCPKG_LIBRARY_LINKAGE static)
else()
    set(VCPKG_LIBRARY_LINKAGE dynamic)
endif()

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_CMAKE_SYSTEM_NAME Android)
set(VCPKG_MAKE_BUILD_TRIPLET "--host=x86_64-linux-android")
set(VCPKG_CMAKE_CONFIGURE_OPTIONS -DANDROID_ABI=x86_64)
set(VCPKG_BUILD_TYPE release)

# Qt requires that the ANDROID_SDK_ROOT is defined when compiling.
set(ANDROID_SDK_ROOT "$ENV{ANDROID_HOME}")
