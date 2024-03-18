set(VCPKG_TARGET_ARCHITECTURE arm64)
# Qt only supports -DANDROID_STL=c++_shared
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CMAKE_SYSTEM_NAME Android)
set(VCPKG_MAKE_BUILD_TRIPLET "--host=aarch64-linux-android")
set(VCPKG_CMAKE_CONFIGURE_OPTIONS -DANDROID_ABI=arm64-v8a)

# Qt requires that the ANDROID_SDK_ROOT is defined when compiling.
set(ANDROID_SDK_ROOT "$ENV{ANDROID_HOME}")
