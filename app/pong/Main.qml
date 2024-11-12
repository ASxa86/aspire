import QtQuick
import aspire

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    color: "blue"
    title: "Pong"

    FrameMetrics {
        id: metric
        thread: FrameMetrics.Thread.Render
    }

    Text {
        text: "FPS: " + metric.fpsRolling.toFixed(0)
        color: "white"
        font.pixelSize: Math.min(window.width, window.height) / 8
    }

    ButtonCircle {
        property point center: Qt.point(parent.width / 8, parent.height / 2)
        width: parent.width * 0.75
        height: width
        x: center.x - width / 2
        y: center.y - height / 2

        onClicked: {
            text.text = parseInt(text.text) - 1;
        } 
    }

    ButtonCircle {
        property point center: Qt.point(parent.width - parent.width / 8, parent.height / 2)
        width: parent.width * 0.75
        height: width    
        x: center.x - width / 2
        y: center.y - height / 2

        onClicked: {
            text.text = parseInt(text.text) + 1;
        }    
    }

    Text {
        id: text
        anchors.centerIn: parent
        text: "40"
        font.pixelSize: Math.min(parent.width, parent.height) / 2
        color: "white"
    }

    // Button - Left
    // Circle {
    //     id: circle
    //     anchors.left: parent.width / 4
    //     radius: parent.width / 4
    //     color: "white"
    //     opacity: 0.25

    //     Circle {
    //         id: subcircle
    //         anchors.centerIn: parent
    //         radius: parent.width / 2
    //         color: "white"
    //         opacity: 0.25

    //         NumberAnimation {
    //             id: animation
    //             target: subcircle; property: "radius"; from: circle.radius / 6; to: circle.radius; duration: animation.duration

    //             onStopped: {
    //                 circle.visible = false;
    //             }

    //             onStarted: {
    //                 circle.visible = true;
    //             }
    //         }

    //         function restart() {
    //             circle.visible = true;
    //             animation.restart();
    //         }
    //     }
    // }

    // TapHandler {
    //     onTapped: {
    //         circle.visible = true;
    //         animation.restart();
    //     }
    // }
}
