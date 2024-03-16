
VCPKG_INSTALL_PATH=$2

# If vcpkg already exists, skip downloading it.
if [ -d "$VCPKG_INSTALL_PATH"]; then
    echo "/vcpkg exists. Skipping."
else
    git clone https://github.com/microsoft/vcpkg.git $VCPKG_INSTALL_PATH --depth 1 --branch $1
fi

# Ensure we have nuget and cmake.
cd $VCPKG_INSTALL_PATH
./bootstrap-vcpkg.sh
./vcpkg fetch nuget
./vcpkg fetch cmake