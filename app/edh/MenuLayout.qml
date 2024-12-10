import QtQuick

Item {
    id: root

    readonly property string statePressed: "pressed"
    readonly property string stateReleased: "released"
    property color background: "white"
    property color foreground: "black"
    required property ListModel model

    state: root.stateReleased

    onStateChanged: {
        if(root.state === root.statePressed) {
            layout.count = 0;
        }
    }

    Component {
        id: componentRect
        Rectangle {
            color: "transparent"
            radius: 3
            border.color: root.foreground
            border.width: 2
        }
    }

    LayoutEDH {
        id: layout

        anchors.centerIn: parent
        width: root.width * 0.7
        height: root.height * 0.7
        spacing: 1
        delegate: componentRect
    }

    TapHandler {
        gesturePolicy: TapHandler.WithinBounds

        onTapped: {
            root.state = root.state === root.statePressed ? root.stateReleased : root.statePressed;
        }
    }

    PathView {
        id: path

        anchors.centerIn: parent

        property real radius: 0

        onRadiusChanged: {
            if(radius === 0) {
                if(root.state === root.stateReleased) {
                    layout.count = root.model.count;
                }
            }
        }

        state: root.state

        states: [
            State {
                name: root.statePressed

                PropertyChanges {
                    target: path
                    radius: 80
                }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                property: "radius"
                duration: 350
            }
        }

        model: [1, 2, 3, 4, 5, 6]

        delegate: Rectangle {
            id: rect
            width: root.width
            height: width
            radius: width / 2
            color: root.background
            visible: path.radius > 0

            required property int index
            required property int modelData

            onVisibleChanged: {
                if(visible === true) {
                    rect.z = rect.modelData === root.model.count ? 1 : 0;
                }
            }

            Connections {
                target: root.model

                function onCountChanged() {
                    rect.z = 0;
                }
            }

            LayoutEDH {
                anchors.centerIn: parent
                width: root.width * 0.7
                height: root.height * 0.7
                count: modelData
                spacing: 1
                delegate: componentRect
            }

            TapHandler {
                gesturePolicy: TapHandler.WithinBounds

                onTapped: {
                    Actions.setPlayerTotal(rect.modelData);
                    root.state = root.stateReleased;
                    rect.z = 1;
                }
            }
        }

        path: Path {
            PathAngleArc {
                id: radial

                radiusX: path.radius
                radiusY: path.radius
                startAngle: -90
                sweepAngle: 360
            }
        }
    }
}
