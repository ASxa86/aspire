import QtQuick
import Qt.labs.animation

Item {
    id: view

    clip: true

    property alias sourceComponent: loader.sourceComponent
    property alias source: loader.source
    property alias item: loader.item
    property alias zoom: container.scale

    Rectangle {
        id: container

        color: "steelblue"
        x: -center.x
        y: -center.y
        width: (parent.width / 0.005) * 3
        height: (parent.height / 0.005) * 3

        property point center: Qt.point(width / 2, height / 2)

        // Draw axis lines
        Rectangle {
            id: vertical
            color: "darkturquoise"
            width: 2 / parent.scale
            height: parent.height
            anchors.centerIn: parent
        }

        Rectangle {
            id: horizontal
            color: "darkturquoise"
            width: parent.width
            height: 2 / parent.scale
            anchors.centerIn: parent
        }


        // Define a root item representing the window so that child items loaded by the loader
        // will have positions defined relative to a window if/when they are loaded into a separate
        // application.
        Item {
            id: window
            width: 1280
            height: 720

            // Anchor the window representation's top left corner
            // to the center of the container.
            anchors.left: parent.left
            anchors.leftMargin: parent.center.x
            anchors.top: parent.top
            anchors.topMargin: parent.center.y

            // Draw the bounding box of the window.
            Rectangle {
                id: top
                color: "darkslategray"
                anchors.top: parent.top
                width: parent.width
                height: 2 / container.scale
            }

            Rectangle {
                id: left
                color: "darkslategray"
                anchors.left: parent.left
                width: 2 / container.scale
                height: parent.height
            }

            Rectangle {
                id: bottom
                color: "darkslategray"
                anchors.bottom: parent.bottom
                width: parent.width
                height: 2 / container.scale
            }

            Rectangle {
                id: right
                color: "darkslategray"
                anchors.right: parent.right
                width: 2 / container.scale
                height: parent.height
            }

            Loader {
                id: loader
            }
        }

        WheelHandler {
            property: "scale"
        }

        BoundaryRule on scale {
            minimum: 0.5 / 100.0
            maximum: 7000 / 100.0
        }
    }

    MouseArea {
        anchors.fill: parent

        drag.target: container
    }
}
