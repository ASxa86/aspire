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
            model: 6

            delegate: Button {
                id: control

                autoExclusive: true
                checkable: true
                Layout.fillWidth: true
                Layout.fillHeight: true

                Material.roundedScale: Material.MediumScale

                contentItem: LayoutEDH {
                    count: index + 1
                    delegate:  Rectangle {
                        color: "transparent"
                        radius: 3
                        border.color: !control.enabled ? control.Material.hintTextColor :
                            (control.flat && control.highlighted) || (control.checked && !control.highlighted) ? control.Material.accentColor :
                            control.highlighted ? control.Material.primaryHighlightedTextColor : control.Material.foreground
                        border.width: 4
                    }
                }

                onClicked: {
                    Actions.setPlayerTotal(index + 1);
                }
            }
        }
    }
}