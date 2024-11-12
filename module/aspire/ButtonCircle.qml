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
            anchors.centerIn: parent
            width: parent.width * 0.25
            height: subcircle.width
            radius: parent.width / 2
            color: "white"
            opacity: circle.opacity

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

    TapHandler {
        onTapped: {
            circle.visible = true;
            animation.restart();
            root.clicked();
        }
    }
}