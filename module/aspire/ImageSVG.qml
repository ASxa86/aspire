import QtQuick

// This class defines an image to support rendering/coloring svg's
Item {
    id: root

    required property url source
    required property color color

    Item {
        id: svg

        anchors.fill: parent

        // Render the svg as a mask to apply on top of a colored rectangle.
        Image {
            id: mask
            anchors.fill: parent
            visible: false
            source: root.source
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            source: icon
            maskEnabled: true
            maskSource: mask
        }

        // Use the mask to render the svg with the rectangle's color.
        Rectangle {
            id: icon
            anchors.fill: parent
            color: root.color
        }
    }
}