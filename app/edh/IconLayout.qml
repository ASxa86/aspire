import QtQuick
import QtQuick.Layouts

// Player Layout
GridLayout {
    id: root
    columns: 2
    rowSpacing: 2
    columnSpacing: 2

    property int count: 3

    Repeater {
        id: repeater

        model: root.count

        delegate: Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: {
                if(root.count == 1) {
                    return 2;
                }
                else if(root.count == 2 || (root.count % 2 != 0 && index == root.count - 1)) {
                    return 2;
                }
            }

            color: "transparent"
            border.color: "black"
            border.width: 2
            radius: 4
        }
    }
}
