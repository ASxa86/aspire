import QtQuick
import QtQuick.Effects

Item {
    id: root

    signal clicked()

    Rectangle {
        id: mask

        anchors.fill: parent
        radius: root.width / 2
        visible: false
        layer.enabled: true
    }

    Item {
        id: effect
        visible: false
        anchors.fill: parent
        layer.enabled: true
        layer.effect: MultiEffect {
            source: circle
            maskSource: mask
            maskEnabled: true
        }

        Rectangle {
            id: circle
            visible: false
            anchors.fill: parent
            color: Qt.rgba(1, 1, 1, 0.25)
            radius: root.width / 2

            Rectangle {
                id: subcircle

                property point center: Qt.point()
                x: center.x - width / 2
                y: center.y - height / 2
                width: circle.width * 0.25
                height: subcircle.width
                radius: circle.width / 2
                color: circle.color

                NumberAnimation {
                    id: animation
                    target: subcircle
                    property: "width"
                    from: circle.height * 0.125
                    to: circle.height
                    duration: 350

                    onStopped: {
                        effect.visible = false;
                    }

                    onStarted: {
                        effect.visible = true;
                    }
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