import QtQuick

Item {
    id: root

    property real radius: width / 2 * 0.75 - 2
    property bool opened: false
    property real itemSize: menu.width / internal.model.count

    // Defining a default property to override Item's children.
    // The items from this list will be added via the ObjectModel using a View instead.
    default property alias items: internal.model.children

    QtObject {
        id: internal

        property ObjectModel model: ObjectModel {
        }
    }

    function open() {
        root.opened = true;
    }

    function close() {
        root.opened = false;
    }

    function toggle() {
        root.opened = !root.opened;
    }

    states: [
        State {
            name: "opened"
            when: menu.opened == true

            PropertyChanges {
                target: menu
                itemSize: menu.width
            }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation {
                property: "itemSize"
                duration: 350
            }
        }
    ]

    PathView {
        id: path

        anchors.centerIn: parent

        property real startAngle: -90

        states: [
            State {
                name: "opened"
                when: root.opened == true

                PropertyChanges {
                    target: root
                    radius: width * 2
                }

                PropertyChanges {
                    target: path
                    startAngle: 270
                }
            }
        ]

        transitions: [
            Transition {
                ParallelAnimation {
                    NumberAnimation {
                        property: "radius"
                        duration: 350
                    }

                    NumberAnimation {
                        property: "startAngle"
                        duration: 350
                    }
                }
            }
        ]

        // state: root.state
        // states: [
        //     State {
        //         name: root.statePressed

        //         PropertyChanges {
        //             target: path
        //             startAngle: 270
        //         }
        //     }
        // ]

        // transitions: Transition {
        //     NumberAnimation {
        //         property: "startAngle"
        //         duration: 350
        //     }
        // }

        model: internal.model

        // delegate: Rectangle {
        //     id: rect
        //     width: root.width / 5
        //     height: width
        //     radius: width / 2
        //     color: foreground

        //     state: root.state
        //     states: [
        //         State {
        //             name: root.statePressed

        //             PropertyChanges {
        //                 target: rect
        //                 width: Style.iconSize * 1.25
        //             }
        //         }
        //     ]

        //     transitions: Transition {
        //         NumberAnimation {
        //             property: "width"
        //             duration: 350
        //         }
        //     }

        //     Loader {
        //         active: root.state === root.statePressed
        //         anchors.fill: parent
        //         sourceComponent: component
        //     }
        // }

        path: Path {
            PathAngleArc {
                id: radial

                radiusX: root.radius
                radiusY: root.radius
                startAngle: path.startAngle
                sweepAngle: 360
            }
        }
    }
}