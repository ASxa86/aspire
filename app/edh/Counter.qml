import QtQuick
import QtQuick.Layouts
import aspire

Item {
    id: root

    clip: true

    required property int index
    required property color background
    required property bool selected
    required property int life
    required property int time
    required property ModelPlayers model

    Rectangle {
        id: mask
        anchors.fill: parent
        radius: width / 32
        visible: false
        layer.enabled: true
    }

    Rectangle {
        id: glow
        anchors.fill: parent
        layer.enabled: true
        layer.effect: MultiEffect {
            blurEnabled: true
            blur: 0.25
            brightness: 0.4
        }

        radius: mask.radius
        color: "darkgoldenrod"
        opacity: selected ? 1 : 0
        scale: 0.99

        TapHandler {
            onLongPressed: {
                Actions.select(index);
            }
        }
    }

    Item {
        id: itemCounter

        anchors.fill: parent
        layer.enabled: true
        layer.effect: MultiEffect {
            source: counter
            maskSource: mask
            maskEnabled: true
        }

        scale: 0.975

        Rectangle {
            id: counter
            anchors.fill: parent

            gradient: Gradient {
                GradientStop { position: 0.0; color: root.background }
                GradientStop { position: 1.0; color: Qt.darker(root.background) }
            }

            ButtonCircle {
                property point center: Qt.point(parent.width / 8, parent.height / 2)
                width: parent.width * 0.75
                height: width
                x: center.x - width / 2
                y: center.y - height / 2

                onClicked: Actions.updateLife(root.index, root.life - 1)
            }

            ButtonCircle {
                property point center: Qt.point(parent.width - parent.width / 8, parent.height / 2)
                width: parent.width * 0.75
                height: width    
                x: center.x - width / 2
                y: center.y - height / 2

                onClicked: Actions.updateLife(root.index, root.life + 1)
            }

            TextEDH {
                anchors.centerIn: parent
                font.pixelSize: Math.min(parent.width, parent.height) / 3
                text: root.life.toString()
            }

            Rectangle {
                width: parent.width
                height: parent.height * 0.1

                Component.onCompleted: {
                    color = Style.color.cardback;
                    color.a = 0.3;
                }

                TextEDH {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: parent.height
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 15
                    text: Qt.formatTime(new Date(root.time), "mm:ss")
                }
            }

            Timer {
                id: timer
                interval: 100
                repeat: true
                running: root.selected

                onTriggered: Actions.updateTime(root.index, root.time + interval)
            }
        }
    }

    Rectangle {
        radius: 4
        color: Qt.rgba(1.0, 1.0, 1.0, 0.75)

        property real pixelsWidth: Style.pixelsPerInch * 0.4
        property real pixelsHeight: Style.pixelsPerInch * 0.5

        width: root.rotation === 0 || root.rotation === 180 ? pixelsWidth : pixelsHeight
        height: root.rotation === 0 || root.rotation === 180 ? pixelsHeight : pixelsWidth

        anchors.horizontalCenter: itemCounter.horizontalCenter
        anchors.bottom: itemCounter.bottom
        anchors.bottomMargin: Style.pixelsPerInch * 0.05

        GridLayout {
            id: layout

            anchors.centerIn: parent
            width: root.rotation === 0 || root.rotation === 180 ? parent.width * 0.9 : parent.height * 0.9
            height: root.rotation === 0 || root.rotation === 180 ? parent.height * 0.9 : parent.width * 0.9
            rotation: root.rotation === 0 || root.rotation === 180 ? root.rotation : root.rotation - 180

            columns: 2
            rowSpacing: 1
            columnSpacing: 1

            Repeater {
                id: repeater

                model: root.model

                delegate: Item {
                    required property int index
                    required property color background
                    required property int angle
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.columnSpan: 
                        root.model.count == 1 ||
                        root.model.count == 2 || 
                        (root.model.count % 2 != 0 && index == root.model.count - 1) ? 2 : 1

                    Rectangle {
                        id: commander
                        anchors.centerIn: parent
                        width: (commander.rotation == 0 || commander.rotation == 180) ? parent.width : parent.height
                        height: (commander.rotation == 0 || commander.rotation == 180)? parent.height : parent.width
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: background }
                            GradientStop { position: 1.0; color: Qt.darker(background) }
                        }
                        rotation: angle
                    }

                    TextEDH {
                        anchors.centerIn: commander
                        font.pixelSize: Math.min(commander.width, commander.height)
                        text: "0"
                        rotation: root.rotation
                    }
                }
            }
        }
    }
}