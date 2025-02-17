import QtQuick

Item {
    Rectangle {
        color: "red"
        x: 50
        y: 50
        width: 32
        height: 32

        Text {
            text: "red"
            color: "white"
            font.pointSize: 12
        }
    }

    Rectangle {
        color: "green"
        x: 120
        y: 120
        width: 64
        height: 32

        Rectangle {
            color: "white"
            height: 16
            width: 16
            radius: 8
            x: 90
        }

        Rectangle {
            color: "white"
            height: 16
            width: 16
            radius: 8
            x: -30
        }
    }
}