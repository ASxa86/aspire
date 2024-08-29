import QtQuick

Rectangle {
    id: root

    property int value: 0

    border.color: "black"
    border.width: 2
    color: Qt.rgba(0.5, 0.5, 0.5, 0.5)

    Text {
        id: text

        anchors.fill: text.parent
        text: root.value.toString()
        font.pixelSize: text.height
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: left

        height: root.height
        width: root.width / 2

        onClicked: {
            root.value -= 1;
        }
    }

    MouseArea {
        id: right

        x: root.width / 2
        height: root.height
        width: root.width / 2

        onClicked: {
            root.value += 1;
        }
    }
}
