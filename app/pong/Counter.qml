import QtQuick
import aspire

Rectangle {
    id: root

    property int value: 40

    ButtonCircle {
        property point center: Qt.point(parent.width / 8, parent.height / 2)
        width: parent.width * 0.75
        height: width
        x: center.x - width / 2
        y: center.y - height / 2

        onClicked: {
            root.value -= 1;
        } 
    }

    ButtonCircle {
        property point center: Qt.point(parent.width - parent.width / 8, parent.height / 2)
        width: parent.width * 0.75
        height: width    
        x: center.x - width / 2
        y: center.y - height / 2

        onClicked: {
            root.value += 1;
        }    
    }

    Text {
        id: text
        anchors.centerIn: parent
        text: root.value.toString()
        font.pixelSize: Math.min(parent.width, parent.height) / 2
        color: "white"
    }
}
