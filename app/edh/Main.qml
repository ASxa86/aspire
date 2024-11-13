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
        columnSpacing: parent.width / 20

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

                Rectangle {
                    id: glow
                    anchors.fill: parent
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        blurEnabled: true
                        blur: 0.8
                    }

                    radius: width / 16
                    color: "gold"
                    scale: 0.98
                    opacity: 0

                    TapHandler {
                        onLongPressed: {
                            glow.opacity = 1;
                        }
                    }
                }

                Item {
                    anchors.fill: parent
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        source: counter
                        maskSource: mask
                        maskEnabled: true
                    }

                    scale: 0.97

                    Counter {
                        id: counter
                        anchors.fill: parent

                        color: colors[index]

                        Connections {
                            target: refresh

                            function onTapped() {
                                counter.value = 40;
                            }
                        }
                    }
                }
            }
        }
    }

    ColumnLayout {
        anchors.centerIn: parent

        spacing: window.height / 2

        ImageSVG {
            source: Icons.refresh
            color: "white"

            Layout.preferredWidth: window.width / 24
            Layout.preferredHeight: window.width / 24

            TapHandler {
                id: refresh
            }
        }

        ImageSVG {
            source: Icons.home
            color: "white"

            Layout.preferredWidth: window.width / 24
            Layout.preferredHeight: window.width / 24
        }
    }

    FrameMetrics {
        id: metric
        thread: FrameMetrics.Thread.Render
    }

    Text {
        text: "FPS: " + metric.fpsRolling.toFixed(0)
        color: "white"
        font.pixelSize: Math.min(window.width, window.height) / 16
    }
}
