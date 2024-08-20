import QtQuick
import aspire

Rectangle {
    width: 1280
    height: 720
    anchors.fill: parent
    color: "blue"
    border.width: 4
    border.color: "grey"

    Counter {
        color: "red"
        width: parent.width / 2
        height: parent.height / 2
        rotation: 180
        value: 40
    }

    Counter {
        color: "blue"
        x: parent.width / 2
        width: parent.width / 2
        height: parent.height / 2
        rotation: 180
        value: 40
    }

    Counter {
        color: "green"
        y: parent.height / 2
        width: parent.width / 2
        height: parent.height / 2
        value: 40
    }

    Counter {
        color: "brown"
        y: parent.height / 2
        x: parent.width / 2
        width: parent.width / 2
        height: parent.height / 2
        value: 40
    }

    FrameMetrics {
        id: metrics

        thread: FrameMetrics.Thread.Render
    }

    Text {
        text: metrics.fpsRolling.toFixed(2)
        color: "white"
        font.pixelSize: 50
    }
}