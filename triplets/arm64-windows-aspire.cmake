set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_TARGET_ARCHITECTURE arm64)
set(VCPKG_CRT_LINKAGE dynamic)

# Only use Qt as shared libraries.
if(${PORT} MATCHES "qt")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
endif()
