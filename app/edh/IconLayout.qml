import QtQuick
import QtQuick.Layouts

// Player Layout
GridLayout {
    id: root
    columns: 2
    rowSpacing: 3
    columnSpacing: 3

    property int count: 3

    Repeater {
        id: repeater

        model: root.count

        delegate: Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.columnSpan: {
                if(root.count == 1) {
                    return 2;
                }
                else if(root.count == 2 || (root.count % 2 != 0 && index == root.count - 1)) {
                    return 2;
                }
                else {
                    return 1;
                }
            }

            color: "transparent"
            border.color: "black"
            border.width: 3
            radius: 4
        }
    }
}
