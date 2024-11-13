import QtQuick
import aspire

Rectangle {
    id: root

    property alias text: txtLife.text
    property alias textTime: time.text
    property bool active: false

    signal decrementClicked()
    signal incrementClicked()
    signal timeTriggered(int seconds)

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

    Rectangle {
        width: parent.width
        height: parent.height * 0.1
        color: Qt.rgba(0, 0, 0, 0.3)

        Text {
            id: time
            color: "white"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
    }

    onActiveChanged: {
        timer.running = root.active
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true

        onTriggered: {
            root.timeTriggered(interval / 1000)
        }
    }
}
