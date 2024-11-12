import QtQuick
import QtQuick.Layouts
import aspire

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    color: "black"
    title: "EDH"

    FrameMetrics {
        id: metric
        thread: FrameMetrics.Thread.Render
    }

    property var colors: [
        "firebrick",
        "forestgreen",
        "darkcyan",
        "slategray"
    ]

    GridLayout {
        id: layout
        anchors.fill: parent
        columns: 2
        rows: 2

        Repeater {
            model: 4

            delegate: Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                rotation: index < layout.rows == 0 ? 0 : 180
                clip: true

                Rectangle {
                    id: mask
                    anchors.fill: parent
                    radius: width / 16
                    visible: false
                    layer.enabled: true
                }

                Item {
                    anchors.fill: parent
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        source: counter
                        maskSource: mask
                        maskEnabled: true
                    }

                    Counter {
                        id: counter
                        anchors.fill: parent

                        color: colors[index]
                    }
                }
            }
        }
    }

    Text {
        text: "FPS: " + metric.fpsRolling.toFixed(0)
        color: "white"
        font.pixelSize: Math.min(window.width, window.height) / 8
    }
}
