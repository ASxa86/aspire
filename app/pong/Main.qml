import QtQuick
import QtQuick.Layouts
import aspire

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    color: "black"
    title: "Pong"

    FrameMetrics {
        id: metric
        thread: FrameMetrics.Thread.Render
    }

    Text {
        text: "FPS: " + metric.fpsRolling.toFixed(0)
        color: "white"
        font.pixelSize: Math.min(window.width, window.height) / 8
    }

    GridLayout {
        id: layout
        anchors.fill: parent
        columns: 2
        rows: 2

        Repeater {
            model: 4

            delegate: Counter {
                clip: true
                Layout.fillWidth: true
                Layout.fillHeight: true

                rotation: index < layout.rows == 0 ? 0 : 180
                color: "coral"
                radius: width / 16
            }
        }
    }
}
