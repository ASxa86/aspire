import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Drawer {
    id: popup

    background: Rectangle {
        topLeftRadius: 16
        topRightRadius: 16
        color: Style.color.cardback
    }

    contentItem: GridLayout {
        rows: 2
        columns: 3

        Layout.margins: 4

        Repeater {
            model: ListModel {
                id: model

                Component.onCompleted: {
                    model.append({
                        life: 10,
                        heart: Style.color.plainsBG,
                        foreground: Style.color.plains,
                        outline: true
                    });

                    model.append({
                        life: 20,
                        heart: Style.color.islandBG,
                        foreground: Style.color.island,
                        outline: false
                    });

                    model.append({
                        life: 30,
                        heart: Style.color.swampBG,
                        foreground: Style.color.swamp,
                        outline: false
                    });

                    model.append({
                        life: 40,
                        heart: Style.color.mountainBG,
                        foreground: Style.color.mountain,
                        outline: false
                    });

                    model.append({
                        life: 50,
                        heart: Style.color.forestBG,
                        foreground: Style.color.forest,
                        outline: false
                    });

                    model.append({
                        life: 60,
                        heart: Style.color.forestBG,
                        foreground: Style.color.forest,
                        outline: false
                    });
                }
            }

            delegate: Button {
                id: control

                Layout.fillWidth: true
                Layout.fillHeight: true

                Material.roundedScale: Material.MediumScale
                Material.background: "transparent"

                contentItem: ImageSVG {
                    anchors.fill: parent
                    source: Icons.heart_filled
                    color: heart

                    TextEDH {
                        id: text

                        text: life
                        style: outline == true ? Text.Outline : Text.Normal
                        color: foreground
                        font.pointSize: 40
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        anchors.fill: parent
                    }
                }

                onClicked: {
                    Actions.reset(life);
                    popup.close();
                }
            }
        }
    }
}