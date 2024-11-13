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

    ListModel {
        id: player

        ListElement {
            color: "firebrick"
            selected: false
        }

        ListElement {
            color: "forestgreen"
            selected: false
        }

        ListElement {
            color: "darkcyan"
            selected: false
        }

        ListElement {
            color: "slategrey"
            selected: false
        }

        function clear() {
            for(let i = 0; i < player.count; i++) {
                player.set(i, {"selected": false});
            }
        }
    }

    GridLayout {
        id: layout
        anchors.fill: parent
        columns: 2
        rows: 2
        columnSpacing: parent.width / 20

        Repeater {
            id: repeater

            model: player

            delegate: Item {
                id: item

                Layout.fillHeight: true
                Layout.fillWidth: true

                required property int index
                required property color color
                required property bool selected

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
                        blur: 0.75
                        brightness: 0.5
                    }

                    radius: width / 16
                    color: "gold"
                    scale: 0.97
                    opacity: item.selected ? 1 : 0

                    TapHandler {
                        onLongPressed: {
                            player.clear();
                            player.set(index, {"selected": true});
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

                    scale: 0.96

                    Counter {
                        id: counter
                        anchors.fill: parent

                        color: item.color

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
