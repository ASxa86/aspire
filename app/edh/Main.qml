import QtQuick
import QtQuick.Layouts
import aspire
import app.edh

Window {
    id: window
    width: 560
    height: 996
    visible: true
    visibility: Qt.platform.os == "android" ? Window.FullScreen : Window.AutomaticVisibility
    color: Style.color.darkcardback
    title: "EDH"

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
                Layout.columnSpan: (counter.rotation == 0 || counter.rotation == 180) ? 2 : 1

                required property int index
                required property color background
                required property bool selected
                required property int life
                required property int time

                function calcRotation() {
                    if(player.count == 1) {
                        return 0;
                    }
                    else if(player.count == 2 && root.index == 0) {
                        return 180;
                    }
                    else if(player.count == 2 || (player.count % 2 != 0 && root.index == player.count - 1)) {
                        return 0;
                    }
                    else if(root.index % 2 == 0) {
                        return 90;
                    }
                    else {
                        return 270;
                    }
                }

                Counter {
                    id: counter
                    width: (counter.rotation == 0 || counter.rotation == 180) ? parent.width : parent.height
                    height: (counter.rotation == 0 || counter.rotation == 180)? parent.height : parent.width
                    anchors.centerIn: parent
                    rotation: calcRotation()
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
        visible: menu.state == menu.statePressed

        Component.onCompleted: {
            shade.color = Style.color.darkcardbackBG;
            shade.color.a = 0.75;
        }

        TapHandler {
            gesturePolicy: TapHandler.WithinBounds

            onTapped: {
                menu.state = menu.stateReleased;
            }
        }
    }

    // MenuEDH {
    //     id: menu
    //     anchors.centerIn: parent

    //     menuItemForest: MenuLife {
    //     }

    //     menuItemPlains: MenuLayout {
    //         model: player
    //         background: Style.color.plains
    //         foreground: Style.color.swamp
    //     }
    // }

    Rectangle {
        anchors.centerIn: parent
        width: 32
        height: 32
        radius: width / 2
        color: Style.color.cardback

        TapHandler {
            gesturePolicy: TapHandler.WithinBounds
            onTapped: menu.toggle()
        }

        RadialMenu {
            id: menu

            anchors.fill: parent

            // animationStyle: RadialMenu.Rotate | RadialMenu.Expand | RadialMenu.Scale

            Rectangle {
                width: menu.itemSize
                height: menu.itemSize
                radius: width / 2
                color: Style.color.plains
            }

            Rectangle {
                width: menu.itemSize
                height: menu.itemSize
                radius: width / 2
                color: Style.color.island
            }

            Rectangle {
                width: menu.itemSize
                height: menu.itemSize
                radius: width / 2
                color: Style.color.swamp
            }

            Rectangle {
                width: menu.itemSize
                height: menu.itemSize
                radius: width / 2
                color: Style.color.mountain
            }

            Rectangle {
                width: menu.itemSize
                height: menu.itemSize
                radius: width / 2
                color: Style.color.forest
            }

            Rectangle {
                width: menu.itemSize
                height: menu.itemSize
                radius: width / 2
                color: "pink"
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
}
