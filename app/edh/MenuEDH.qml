import QtQuick

Rectangle {
    id: root

    width: Style.iconSize
    height: Style.iconSize
    radius: width / 2
    color: Style.color.lightcardback
    border.color: Style.color.lightcardbackBG
    border.width: 2

    property Component menuItemForest: Item {}
    property Component menuItemPlains: Item {}
    property Component menuItemMountain: Item {}
    property Component menuItemIsland: Item {}
    property Component menuItemSwamp: Item {}

    state: stateReleased.name

    states: [
        State {
            id: stateReleased
            name: "released"

            PropertyChanges {
                target: path
                radius: root.radius * 0.75 - 2
            }
        },
        State {
            id: statePressed
            name: "pressed"

            PropertyChanges {
                target: path
                radius: root.width * 2
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            property: "radius"
            duration: 350
        }
    }
    
    PathView {
        id: path

        anchors.centerIn: parent

        property real radius: root.radius * 0.75 - 2
        property real startAngle: -90


        state: root.state
        states: [
            State {
                name: statePressed.name

                PropertyChanges {
                    target: path
                    startAngle: 270
                }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                property: "startAngle"
                duration: 350
            }
        }

        model: ListModel {
            id: model

            Component.onCompleted: {
                model.append({
                    foreground: Style.color.plains,
                    component: root.menuItemPlains
                });

                model.append({
                    foreground: Style.color.island,
                    component: root.menuItemIsland
                });

                model.append({
                    foreground: Style.color.swamp,
                    component: root.menuItemSwamp
                });

                model.append({
                    foreground: Style.color.mountain,
                    component: root.menuItemMountain
                });

                model.append({
                    foreground: Style.color.forest,
                    component: root.menuItemForest
                });
            }
        }

        delegate: Rectangle {
            id: rect
            width: root.width / 5
            height: width
            radius: width / 2
            color: foreground

            state: root.state
            states: [
                State {
                    name: statePressed.name

                    PropertyChanges {
                        target: rect
                        width: Style.iconSize
                    }
                },
                State {
                    name: stateReleased.name

                    PropertyChanges {
                        target: rect
                        width: root.width / 5
                    }
                }
            ]

            transitions: Transition {
                NumberAnimation {
                    property: "width"
                    duration: 350
                }
            }

            Loader {
                // anchors.fill: parent
                width: parent.width * 0.75
                height: parent.height * 0.75
                anchors.centerIn: parent
                sourceComponent: component
            }

            TapHandler {
                gesturePolicy: TapHandler.WithinBounds
            }
        }

        path: Path {
            PathAngleArc {
                id: radial

                radiusX: path.radius
                radiusY: path.radius
                startAngle: path.startAngle
                sweepAngle: 360
            }
        }
    }

    TapHandler {
        id: tapHandler
        gesturePolicy: TapHandler.WithinBounds

        onTapped: {
            root.state = root.state == statePressed.name ? stateReleased.name : statePressed.name;
        }
    }
}