vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO libsdl-org/SDL_mixer
    REF main
    SHA512 66ccce01e1b677861177dc2bac87e68b8a9abaf4c75b17f7a0ef64709a3540f62f9826d94ff89206287908c1b2987f88d33551cf7f48583bcc03e35f2872a674
    # PATCHES 
    #     fix-pkg-prefix.patch
)

vcpkg_check_features(
    OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        fluidsynth SDLMIXER_MIDI
        fluidsynth SDLMIXER_MIDI_FLUIDSYNTH
        libflac SDLMIXER_FLAC
        libflac SDLMIXER_FLAC_LIBFLAC
        libmodplug SDLMIXER_MOD
        libmodplug SDLMIXER_MOD_MODPLUG
        mpg123 SDLMIXER_MP3
        mpg123 SDLMIXER_MP3_MPG123
        wavpack SDLMIXER_WAVPACK
        wavpack SDLMIXER_WAVPACK_DSD
        opusfile SDLMIXER_OPUS
)

if("fluidsynth" IN_LIST FEATURES)
    vcpkg_find_acquire_program(PKGCONFIG)
    list(APPEND EXTRA_OPTIONS "-DPKG_CONFIG_EXECUTABLE=${PKGCONFIG}")
endif()

string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "dynamic" BUILD_SHARED)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        ${FEATURE_OPTIONS}
        ${EXTRA_OPTIONS}
        -DSDLMIXER_VENDORED=OFF
        -DSDLMIXER_SAMPLES=OFF
        -DSDLMIXER_DEPS_SHARED=OFF
        -DSDLMIXER_OPUS_SHARED=OFF
        -DSDLMIXER_VORBIS_VORBISFILE_SHARED=OFF
        -DSDLMIXER_VORBIS="VORBISFILE"
        -DSDLMIXER_FLAC_DRFLAC=OFF
        -DSDLMIXER_MIDI_NATIVE=OFF
        -DSDLMIXER_MIDI_TIMIDITY=OFF
        -DSDLMIXER_MP3_DRMP3=OFF
        -DSDLMIXER_MOD_XMP_SHARED=${BUILD_SHARED}
    MAYBE_UNUSED_VARIABLES
        SDLMIXER_MP3_DRMP3
)

vcpkg_cmake_install()
vcpkg_copy_pdbs()
vcpkg_cmake_config_fixup(
    PACKAGE_NAME "SDL3_mixer"
    CONFIG_PATH "cmake"
)
vcpkg_fixup_pkgconfig()

if(NOT VCPKG_BUILD_TYPE)
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/sdl3-mixer.pc" "-lSDL3_mixer" "-lSDL3_mixerd")
endif()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE.txt")