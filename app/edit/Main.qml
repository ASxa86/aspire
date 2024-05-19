import QtQuick

Rectangle {
    anchors.fill: parent
    color: "blue"
    border.width: 4
    border.color: "grey"

    Text {
        anchors.centerIn: parent
        text: "Hello"
        color: "white"
        font.pixelSize: 50
    }

    Square {
        id: square
        x: 300
        y: 40
        rotation: 30

        MouseArea {
            anchors.fill: parent

            drag.target: square
        }
    }
}