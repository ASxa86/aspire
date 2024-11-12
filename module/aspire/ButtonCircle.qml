import QtQuick
import QtQuick.Effects

Item {
    id: root

    signal clicked()

    // Rectangle {
    //     id: mask

    //     anchors.fill: parent
    //     radius: root.width / 2
    //     visible: false
    //     color: "white"
    //     layer.enabled: true
    // }

    Rectangle {
        id: circle
        visible: false
        anchors.fill: parent
        color: "white"
        opacity: 0.25
        radius: root.width / 2

        Rectangle {
            id: subcircle

            property point center: Qt.point()
            x: center.x - width / 2
            y: center.y - height / 2
            width: circle.width * 0.25
            height: subcircle.width
            radius: circle.width / 2
            color: "white"
            opacity: 0.25
            visible: true

            NumberAnimation {
                id: animation
                target: subcircle
                property: "width"
                from: circle.height * 0.125
                to: circle.height
                duration: 350

                onStopped: {
                    circle.visible = false;
                }

                onStarted: {
                    circle.visible = true;
                }
            }
        }
    }

    // MultiEffect {
    //     id: effect
    //     source: circle
    //     anchors.fill: parent
    //     maskSource: mask
    //     maskEnabled: true
    //     maskInverted: false
    //     visible: false
    //     opacity: 0.15
    // }

    TapHandler {
        onTapped: (point) => {
            subcircle.center = root.mapFromGlobal(point.globalPosition);
            animation.restart();
            root.clicked();
        }
    }
}