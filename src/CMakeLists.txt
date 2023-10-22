project(aspire)

project_add_qml_module(
    SOURCES
        ${PROJECT_INCLUDE_DIR}/aspire/Aspire.h
        Aspire.cpp
)

project_gen_export()
project_install_target()
