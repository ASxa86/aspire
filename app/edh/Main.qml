import QtQuick
import QtQuick.Layouts
import aspire
import app.edh

Window {
    id: window
    width: 560
    height: width * 16 / 9
    visible: true
    visibility: Qt.platform.os == "android" ? Window.FullScreen : Window.AutomaticVisibility
    color: Style.color.darkcardback
    title: "EDH"

    Component.onCompleted: {
        Actions.setPlayerTotal(6);
    }

    ModelPlayers {
        id: player
    }

    // Player Layout
    GridLayout {
        id: layout
        anchors.fill: parent
        columns: 2
        rows: 2
        rowSpacing: 0
        columnSpacing: 0

        Repeater {
            id: repeater

            model: player

            delegate: Item {
                id: root
                Layout.fillHeight: true
                Layout.fillWidth: true

                required property int index
                required property color background
                required property bool selected
                required property int life
                required property int time

                Counter {
                    width: parent.height
                    height: parent.width
                    anchors.centerIn: parent
                    rotation: root.index % 2 == 0 ? 90 : 270
                    index: root.index
                    background: root.background
                    selected: root.selected
                    life: root.life
                    time: root.time
                }
            }
        }
    }

    // Menu shading
    Rectangle {
        id: shade
        anchors.fill: parent
        visible: menu.state == "pressed"

        Component.onCompleted: {
            shade.color = Style.color.darkcardbackBG;
            shade.color.a = 0.75;
        }

        TapHandler {
            gesturePolicy: TapHandler.WithinBounds

            onTapped: {
                menu.state = "released"
            }
        }
    }

    MenuEDH {
        id: menu
        anchors.centerIn: parent

        menuItemForest: MenuLife {
        }
    }

    // Debugging
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
