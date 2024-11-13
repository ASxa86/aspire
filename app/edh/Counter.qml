import QtQuick
import aspire

Rectangle {
    id: root

    property alias text: txtLife.text

    signal decrementClicked()
    signal incrementClicked()

    ButtonCircle {
        property point center: Qt.point(parent.width / 8, parent.height / 2)
        width: parent.width * 0.75
        height: width
        x: center.x - width / 2
        y: center.y - height / 2

        onClicked: root.decrementClicked()
    }

    ButtonCircle {
        property point center: Qt.point(parent.width - parent.width / 8, parent.height / 2)
        width: parent.width * 0.75
        height: width    
        x: center.x - width / 2
        y: center.y - height / 2

        onClicked: root.incrementClicked()  
    }

    Text {
        id: txtLife
        anchors.centerIn: parent
        font.pixelSize: Math.min(parent.width, parent.height) / 2
        color: "white"
    }
}
