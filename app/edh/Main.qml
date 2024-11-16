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

    // Player Layout
    GridLayout {
        id: layout
        anchors.fill: parent
        columns: 2
        rows: 2
        columnSpacing: parent.width / 20

        Repeater {
            id: repeater

            model: player

            delegate: Counter {
                Layout.fillHeight: true
                Layout.fillWidth: true

                rotation: index < layout.rows == 0 ? 0 : 180
            }
        }
    }

    // Menu shading
    Rectangle {
        id: shade
        anchors.fill: parent
        visible: menuLife.active

        Component.onCompleted: {
            shade.color = Style.color.darkcardbackBG;
            shade.color.a = 0.75;
        }

        TapHandler {
            gesturePolicy: TapHandler.WithinBounds

            onTapped: {
                menuLife.active = false;
            }
        }
    }

    // Menu Options
    Column {
        id: menu
        anchors.centerIn: parent

        property point center: Qt.point(width / 2, height / 2)
        property int count: children.length
        spacing: window.height / count

        MenuLife {
            id: menuLife
            width: window.width / 24
            height: width
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
