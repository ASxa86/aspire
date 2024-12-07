project(aspire)

set(QML_SINGLETONS
    Fonts.qml
    Icons.qml
)

set_source_files_properties(${QML_SINGLETONS}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION 1.0
    SOURCES
        Aspire.cpp
        Aspire.h
        FrameMetrics.cpp
        FrameMetrics.h
        Meters.cpp
        Meters.h
    QML_FILES
        ButtonCircle.qml
        ImageSVG.qml
        Square.qml
        ${QML_SINGLETONS}
    RESOURCES
        icons/apps.svg
        icons/envelope.svg
        icons/facebook.svg
        icons/heart.svg
        icons/heart_filled.svg
        icons/home.svg
        icons/instagram.svg
        icons/phone-call.svg
        icons/refresh.svg
        icons/search.svg
        icons/user.svg
        fonts/DavidLibre-Regular.ttf
        fonts/DavidLibre-Bold.ttf
        fonts/DavidLibre-Medium.ttf
    IMPORTS
        QtQuick
        QtQuick.Effects
)

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/export.hxx BASE_NAME ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Quick
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
