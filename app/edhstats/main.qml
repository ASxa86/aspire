import QtQuick
import QtQuick.Layouts
import aspire

Window {
    id: window
    title: "EDH Stats"
    visible: true
    width: 1920
    height: 1080
    color: "black"

    GridLayout {
        anchors.fill: parent
        rows: 2
        columns: 2
        Repeater {
            model: ListModel {

                ListElement {
                    life: 40
                    color: "darkred"
                    invert: true
                }

                ListElement {
                    life: 40
                    color: "cornflowerblue"
                    invert: true
                }

                ListElement {
                    life: 40
                    color: "forestgreen"
                    invert: false
                }

                ListElement {
                    life: 40
                    color: "darkorchid"
                    invert: false
                }
            }

            delegate: Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: model.color
                rotation: model.invert ? 180 : 0

                Text {
                    id: text
                    anchors.centerIn: parent
                    text: model.life
                    color: "white"
                    font.pointSize: 42
                    font.bold: true
                }

                Item {
                    width: parent.width / 2
                    height: parent.height
                    TapHandler {
                        onTapped: {
                            model.life -= 1;
                        }
                    }
                }

                Item {
                    x: parent.width / 2
                    width: parent.width / 2
                    height: parent.height
                    TapHandler {
                        onTapped: {
                            model.life += 1;
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: center
        width: 100
        height: 100
        radius: 100
        color: "saddlebrown"
        anchors.centerIn: parent
        border.color: "black"
        border.width: 5

        Repeater {
            id: repeater
            model: ListModel {
                ListElement {
                    color: "white"
                }

                ListElement {
                    color: "blue"
                }

                ListElement {
                    color: "black"
                }

                ListElement {
                    color: "red"
                }

                ListElement {
                    color: "green"
                }
            }

            delegate: Rectangle {
                id: icon
                width: 15
                height: 15
                radius: 15
                color: model.color

                property var angle: index * (360 / repeater.count) - 90
                property var rad: angle * Math.PI / 180
                property var r: 30
                property var centerX: center.width / 2
                property var centerY: center.height / 2
                x: centerX + r * Math.cos(rad) - width / 2
                y: centerY + r * Math.sin(rad) - height / 2

                Component.onCompleted: {
                    console.log(x);
                    console.log(centerX);
                }
            }
        }
    }
}
