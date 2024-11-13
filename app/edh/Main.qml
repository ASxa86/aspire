import QtQuick
import QtQuick.Layouts
import aspire

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    visibility: Window.AutomaticVisibility
    color: "black"
    title: "EDH"

    ListModel {
        id: player

        ListElement {
            color: "darkred"
            selected: false
            life: 40
        }

        ListElement {
            color: "olivedrab"
            selected: false
            life: 40
        }

        ListElement {
            color: "darkcyan"
            selected: false
            life: 40
        }

        ListElement {
            color: "darkslategrey"
            selected: false
            life: 40
        }

        function clear() {
            for(let i = 0; i < player.count; i++) {
                player.set(i, {"selected": false});
            }
        }

        function reset(health) {
            for(let i = 0; i < player.count; i++) {
                player.set(i, {"life": health});
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
                required property int life

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
                        value: item.life
                    }
                }
            }
        }
    }

    Rectangle {
        id: shade
        anchors.fill: parent
        color: Qt.rgba(0, 0, 0, 0.5)
        visible: false

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

        ImageSVG {
            id: refresh
            source: Icons.refresh
            color: "white"
            width: window.width / 24
            height: width

            property point center: Qt.point(width / 2, height / 2)

            TapHandler {
                onTapped: {
                    shade.visible = true;
                }
            }

            Repeater {
                id: rptrReset
                model: 5
                delegate: Rectangle {
                    id: rect
                    width: refresh.width
                    height: width
                    color: "transparent"
                    visible: shade.visible

                    property double angle: index * (360.0 / rptrReset.count) - 90
                    property double rad: angle * Math.PI / 180
                    property double r: refresh.width * 2
                    x: refresh.center.x + r * Math.cos(rad) - rect.width / 2
                    y: refresh.center.y + r * Math.sin(rad) - rect.height / 2

                    Text {
                        id: text

                        color: "white"
                        text: (index + 1) * 10
                        font.pointSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        anchors.fill: parent

                        TapHandler {
                            onTapped: {
                                player.reset(parseInt(text.text));
                                shade.visible = false;
                            }
                        }
                    }
                }
            }
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
    }
}
