import QtQuick
import QtQuick.Layouts
import aspire
import app.edh

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    visibility: Qt.platform.os == "android" ? Window.FullScreen : Window.AutomaticVisibility
    color: Style.color.cardback
    title: "EDH"

    ModelPlayers {
        id: player
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
                required property color background
                required property bool selected
                required property int life
                required property int time

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
                        blur: 0
                        brightness: 0.5
                    }

                    radius: width / 16
                    color: Style.color.darkplainsBG
                    opacity: selected ? 1 : 0

                    TapHandler {
                        onLongPressed: {
                            Actions.select(index);
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

                    scale: 0.99

                    Counter {
                        id: counter
                        anchors.fill: parent

                        gradient: Gradient {
                            GradientStop { position: 0.0; color: background }
                            GradientStop { position: 1.0; color: Qt.darker(background) }
                        }

                        text: life.toString()
                        textTime: Qt.formatTime(new Date(time * 1000), "mm:ss")
                        active: selected

                        onDecrementClicked: {
                            Actions.updateLife(index, life - 1);
                        }

                        onIncrementClicked: {
                            Actions.updateLife(index, life + 1);
                        }

                        onTimeTriggered: (seconds) => {
                            Actions.updateTime(index, time + seconds);
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: shade
        anchors.fill: parent
        visible: false

        Component.onCompleted: {
            shade.color = Style.color.darkcardbackBG;
            shade.color.a = 0.75;
        }

        TapHandler {
            gesturePolicy: TapHandler.WithinBounds

            onTapped: {
                shade.visible = false;
            }
        }
    }

    Column {
        id: menu
        anchors.centerIn: parent

        property point center: Qt.point(width / 2, height / 2)
        property int count: children.length
        spacing: window.height / count

        MenuLife {
            width: window.width / 24
            height: width
        }

        ImageSVG {
            source: Icons.home
            color: "white"

            width: window.width / 24
            height: width
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
        visible: Qt.platform.os !== "android"
    }
}
