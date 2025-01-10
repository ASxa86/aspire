import QtQuick
import aspire

Item {
    id: root

    clip: true

    required property int index
    required property color background
    required property bool selected
    required property int life
    required property int time

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
                font.pixelSize: Math.min(parent.width, parent.height) / 2
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
}