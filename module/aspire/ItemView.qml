import QtQuick
import Qt.labs.animation
import aspire

Item {
    id: view

    clip: true

    property alias sourceComponent: loader.sourceComponent
    property alias source: loader.source
    property alias item: loader.item
    property alias zoom: container.scale

    function save(file) {
        Aspire.writeFile(view.item, file);
    }

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

                onLoaded: {
                    console.log("Loaded: ", loader.source);
                }
            }
        }

        WheelHandler {
            property: "scale"
        }

        DragHandler {
            id: dragHandler
            acceptedButtons: Qt.MiddleButton
        }

        BoundaryRule on scale {
            minimum: 0.5 / 100.0
            maximum: 7000 / 100.0
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        cursorShape: dragHandler.active || current !== null ? Qt.SizeAllCursor : Qt.ArrowCursor

        property Item root: loader.item
        property Item current: null
        property point point: Qt.point(0, 0)

        onPressed: (event) => {
            if (event.button != Qt.LeftButton) {
                return;
            }

            if (root === null) {
                return;
            }

            intersect(root, Qt.point(event.x, event.y));

            if (current !== null) {
                point = Qt.point(event.x, event.y);
            }
        }

        onPositionChanged: (event) => {
            if (current === null) {
                return;
            }

            // To enable smooth movement at any scale,
            // we map the event position to the item's parent
            // and calculate a delta to apply.
            let p = current.parent;
            const start = p.mapFromItem(mouseArea, point);
            const end = p.mapFromItem(mouseArea, Qt.point(event.x, event.y));
            const delta = Qt.point(end.x - start.x, end.y - start.y);
            current.x += delta.x;
            current.y += delta.y;
            point = Qt.point(event.x, event.y);
        }

        onReleased: {
            current = null;
            point = Qt.point(0, 0);
        }

        function intersect(parent, point) {
            for (let i = 0; i < parent.children.length; i++) {
                let child = parent.children[i];

                // Perform a depth first search to intersect with children 
                // that are rendered in front of their parents first.
                intersect(child, point);

                // If an intersection as occurred, let's exit.
                if (current !== null) {
                    return;
                }

                let pos = child.mapFromItem(mouseArea, point);

                if (child.contains(pos)) {
                    current = child;
                    return;
                }
            }
        }
    }
}
