import QtQuick

Item {
    id: root

    property bool active: false

    signal clicked()

    // Animate the menu icon and hearts when menu pops up.
    onActiveChanged: {
        if(root.active == true) {
            animRotateForward.start();
            animRadialForward.start();
        }
        else {
            animRotateReverse.start();
            animRadialReverse.start();
        }
    }

    ImageSVG {
        id: refresh
        source: Icons.refresh
        color: "white"

        anchors.fill: parent

        NumberAnimation {
            id: animRotateForward
            target: refresh
            property: "rotation"
            from: 0
            to: 360
            duration: 350
        }

        NumberAnimation {
            id: animRotateReverse
            target: refresh
            property: "rotation"
            from: 360
            to: 0
            duration: 350
        }

        TapHandler {
            gesturePolicy: TapHandler.WithinBounds
            
            onTapped: {
                root.active = !root.active
            }
        }
    }

    PathView {
        id: path

        anchors.centerIn: parent

        property real radius: 0

        model: ListModel {
            id: model

            Component.onCompleted: {
                model.append({
                    life: 10,
                    background: Style.color.plainsBG,
                    foreground: Style.color.plains,
                    outline: true
                });

                model.append({
                    life: 20,
                    background: Style.color.islandBG,
                    foreground: Style.color.island,
                    outline: false
                });

                model.append({
                    life: 30,
                    background: Style.color.swampBG,
                    foreground: Style.color.swamp,
                    outline: false
                });

                model.append({
                    life: 40,
                    background: Style.color.mountainBG,
                    foreground: Style.color.mountain,
                    outline: false
                });

                model.append({
                    life: 50,
                    background: Style.color.forestBG,
                    foreground: Style.color.forest,
                    outline: false
                });
            }
        }

        delegate: Rectangle {
            id: rect
            width: refresh.width
            height: width
            color: "transparent"
            visible: path.radius > 0

            ImageSVG {
                anchors.fill: parent
                source: Icons.heart_filled
                color: background

                TextEDH {
                    id: text

                    text: life
                    style: outline == true ? Text.Outline : Text.Normal
                    color: foreground
                    font.pointSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    anchors.fill: parent

                    TapHandler {
                        onTapped: {
                            Actions.reset(life);
                            root.active = false;
                        }
                    }
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

        NumberAnimation {
            id: animRadialForward
            target: path
            property: "radius"
            from: 0
            to: 80
            duration: 350
        }

        NumberAnimation {
            id: animRadialReverse
            target: path
            property: "radius"
            from: 80
            to: 0
            duration: 350
        }
    }
}