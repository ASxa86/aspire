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
                }

                ListElement {
                    life: 40
                    color: "cornflowerblue"
                }

                ListElement {
                    life: 40
                    color: "forestgreen"
                }

                ListElement {
                    life: 40
                    color: "darkorchid"
                }
            }

            delegate: Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: model.color

                Text {
                    id: text
                    anchors.centerIn: parent
                    text: model.life
                    color: "white"
                    font.pointSize: 42
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
}
