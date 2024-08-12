import QtQuick
import aspire

Rectangle {
    anchors.fill: parent
    color: "blue"
    border.width: 4
    border.color: "grey"

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

    FrameMetrics {
        id: metrics

        thread: FrameMetrics.Thread.Render
    }

    Text {
        anchors.centerIn: parent
        text: metrics.fpsRolling.toFixed(2)
        color: "white"
        font.pixelSize: 50
    }
}