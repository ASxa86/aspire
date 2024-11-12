import QtQuick

Item {
    id: root

    signal clicked()

    Rectangle {
        id: circle
        visible: false
        anchors.fill: parent
        radius: root.width / 2
        color: "white"
        opacity: 0.25

    Rectangle {
        id: subcircle

        property point center: Qt.point()
        x: center.x - width / 2
        y: center.y - height / 2
        width: circle.width * 0.25
        height: subcircle.width
        radius: circle.width / 2
        color: "white"
        opacity: circle.opacity
        visible: false

            NumberAnimation {
                id: animation
                target: subcircle
                property: "width"
                from: circle.height * 0.125
                to: circle.height
                duration: 350

                onStopped: {
                    subcircle.visible = false;
                    circle.visible = false;
                }

                onStarted: {
                    circle.visible = true;
                    subcircle.visible = true;
                }
            }
        }
    }

    TapHandler {
        onTapped: (point) => {
            subcircle.center = root.mapFromGlobal(point.globalPosition);
            animation.restart();
            root.clicked();
        }
    }
}