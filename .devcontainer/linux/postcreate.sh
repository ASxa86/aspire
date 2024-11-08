#! /bin/bash

if [ -d "$VCPKG_ROOT" ]; then
    echo "$VCPKG_ROOT already exists. Skipping clone."
else
    git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT --depth 1 --branch $VCPKG_VERSION
fi

./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg fetch nuget
./vcpkg/vcpkg fetch cmake
./vcpkg/vcpkg fetch ninja

echo "mono ./vcpkg/downloads/tools/nuget-6.10.0-linux/nuget.exe sources add -source $NUGET_SOURCE -name $NUGET_NAME -username $GITLAB_USER -password $GITLAB_USER_TOKEN"
mono ./vcpkg/downloads/tools/nuget-6.10.0-linux/nuget.exe sources add -source $NUGET_SOURCE -name $NUGET_NAME -username $GITLAB_USER -password $GITLAB_USER_TOKEN
