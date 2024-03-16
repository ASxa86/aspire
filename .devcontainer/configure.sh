bash ./.devcontainer/get-vcpkg.sh ${VCPKG_VERSION} ${VCPKG_INSTALL_PATH}
bash ./.devcontainer/configure-nuget.sh ${NUGET_COMMAND} ${NUGET_SOURCE} ${NUGET_NAME} ${GITLAB_USER} ${GITLAB_TOKEN}