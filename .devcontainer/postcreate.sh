#! /bin/bash

if [ -d "$VCPKG_ROOT" ]; then
    echo "$VCPKG_ROOT already exists. Skipping clone."
else
    git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT --depth 1 --branch $VCPKG_VERSION
fi

./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg fetch nuget
./vcpkg/vcpkg fetch cmake
