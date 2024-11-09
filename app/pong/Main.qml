import QtQuick
import aspire

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    color: "blue"
    title: "Pong"

    FrameMetrics {
        id: metric
        thread: FrameMetrics.Thread.Render
    }

    Text {
        text: "FPS: " + metric.fpsRolling.toFixed(0)
        color: "white"
        font.pixelSize: Math.min(window.width, window.height) / 4
    }

    Square {
        width: 32
        height: 32
    }
}
