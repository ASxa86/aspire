import QtQuick
import Qt.labs.animation
import aspire

// This becomes a Pane at some point?
Rectangle {
    id: view

    color: "darkcyan"
    clip: true

    property int axisWidth: 2
    property color axisColor: "darkkhaki"

    property int windowWidth: 2
    property color windowColor: "darkolivegreen"

    property alias sourceComponent: loader.sourceComponent
    property alias source: loader.source
    property alias item: loader.item
    property alias zoom: container.scale

    function save(file) {
        Aspire.writeFile(view.item, file);
    }

    onWidthChanged: horizontal.update()
    onHeightChanged: vertical.update()

    Item {
        id: container
        width: 1280
        height: 720

        onXChanged: horizontal.update()
        onYChanged: vertical.update()

        // Draw axis lines
        Rectangle {
            id: vertical
            color: view.axisColor
            width: view.axisWidth / parent.scale
            anchors.left: parent.left

            function update() {
                vertical.y = container.mapFromItem(view, 0, 0).y;
                vertical.height = container.mapFromItem(view, view.width, view.height).y - vertical.y;
            }
        }

        Rectangle {
            id: horizontal
            color: view.axisColor
            height: view.axisWidth / parent.scale
            anchors.top: parent.top

            function update() {
                horizontal.x = container.mapFromItem(view, 0, 0).x;
                horizontal.width = container.mapFromItem(view, view.width, view.height).x - horizontal.x;
            }
        }

        // Draw the bounding box of the window.
        Rectangle {
            id: top
            color: view.windowColor
            anchors.top: parent.top
            width: parent.width
            height: view.windowWidth / container.scale
        }

        Rectangle {
            id: left
            color: view.windowColor
            anchors.left: parent.left
            width: view.windowWidth / container.scale
            height: parent.height
        }

        Rectangle {
            id: bottom
            color: view.windowColor
            anchors.bottom: parent.bottom
            width: parent.width
            height: view.windowWidth / container.scale
        }

        Rectangle {
            id: right
            color: view.windowColor
            anchors.right: parent.right
            width: view.windowWidth / container.scale
            height: parent.height
        }

        Loader {
            id: loader

            onLoaded: {
                console.log("Loaded: ", loader.source);
            }
        }

        BoundaryRule on scale {
            minimum: 0.5 / 100.0
            maximum: 7000 / 100.0
        }
    }

    WheelHandler {
        property: "scale"
        target: container
    }

    DragHandler {
        id: dragHandler
        acceptedButtons: Qt.MiddleButton
        target: container
        snapMode: DragHandler.NoSnap
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
