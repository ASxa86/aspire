import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import aspire
import app.edh

ApplicationWindow {
    id: window
    width: 560
    height: 996
    visible: true
    visibility: Qt.platform.os == "android" ? Window.FullScreen : Window.AutomaticVisibility
    // color: Style.color.darkcardback
    title: "EDH"

    Material.theme: Material.Dark
    Material.accent: Style.color.plainsBG
    Material.background: Style.color.darkcardback

    footer: TabBar {
        id: tabBar
        TabButton {
            display: AbstractButton.TextUnderIcon
            text: "home"
            icon.source: Icons.home
        }

        TabButton {
            display: AbstractButton.TextUnderIcon
            text: "charts"
            icon.source: Icons.home
        }

        TabButton {
            display: AbstractButton.TextUnderIcon
            text: "layouts"
            icon.source: Icons.apps
            checkable: false

            onClicked: popup.open()
        }

        TabButton {
            display: AbstractButton.TextUnderIcon
            text: "reset"
            icon.source: Icons.refresh
            checkable: false

            onClicked: popupReset.open()
        }

        TabButton {
            display: AbstractButton.TextUnderIcon
            text: "options"
            icon.source: Icons.home
        }
    }

    Component.onCompleted: {
        Actions.setPlayerTotal(4);
    }

    ModelPlayers {
        id: player
    }

    // Player Layout
    GridLayout {
        id: layout
        anchors.fill: parent
        columns: 2
        rowSpacing: 0
        columnSpacing: 0

        Repeater {
            id: repeater

            model: player

            delegate: Item {
                id: root
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 
                    player.count == 1 ||
                    player.count == 2 || 
                    (player.count % 2 != 0 && root.index == player.count - 1) ? 2 : 1

                required property int index
                required property color background
                required property bool selected
                required property int life
                required property int time
                required property int angle

                Counter {
                    id: counter
                    width: (counter.rotation == 0 || counter.rotation == 180) ? parent.width : parent.height
                    height: (counter.rotation == 0 || counter.rotation == 180)? parent.height : parent.width
                    anchors.centerIn: parent
                    rotation: root.angle
                    index: root.index
                    background: root.background
                    selected: root.selected
                    life: root.life
                    time: root.time
                    model: player
                }
            }
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

    PopupLayout {
        id: popup

        width: parent.width
        height: parent.height / 2
        edge: Qt.BottomEdge
        dragMargin: 0
    }

    PopupReset {
        id: popupReset

        width: parent.width
        height: parent.height / 2
        edge: Qt.BottomEdge
        dragMargin: 0
    }
}
