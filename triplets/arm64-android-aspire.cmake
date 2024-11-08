set(VCPKG_TARGET_ARCHITECTURE arm64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CMAKE_SYSTEM_NAME Android)
set(VCPKG_MAKE_BUILD_TRIPLET "--host=aarch64-linux-android")
set(VCPKG_CMAKE_CONFIGURE_OPTIONS -DANDROID_ABI=arm64-v8a)
set(VCPKG_BUILD_TYPE release)

# Only use Qt as shared libraries.
if(${PORT} MATCHES "qt")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
endif()

# Qt requires that the ANDROID_SDK_ROOT is defined when compiling.
set(ANDROID_SDK_ROOT "$ENV{ANDROID_HOME}")
set(ANDROID_PLATFORM 34)
