import QtQuick
import aspire

Window {
    id: window
    title: "shapes"
    visible: true
    width: 1920
    height: 1080
    color: "black"

    property double rotate: 0

    Timer {
        running: true
        repeat: true
        interval: 10

        onTriggered: {
            window.rotate += interval / 1000.0;
        }
    }

    Item {
        anchors.fill: parent
        rotation: window.rotate

        Repeater {
            id: repeater

            model: ModelEntity {
                id: modelEntity
                count: 4000
            }

            property double radius: Math.min(window.width / 2, window.height / 2)

            delegate: Item {
                x: parent.width / 2
                y: parent.height / 2

                Rectangle {
                    id: rectangle

                    property double angle: Math.random() * 360 * Math.PI / 180
                    x: Math.cos(angle) * repeater.radius * Math.random()
                    y: Math.sin(angle) * repeater.radius * Math.random()
                    width: 32
                    height: 32
                    rotation: model.rotation - window.rotate
                    color: "black"
                    border.color: "green"
                    border.width: 2
                }
            }
        }
    }

    Text {
        anchors.right: parent.right
        text: "Count: " + modelEntity.count
        color: "white"
        font.pixelSize: 75
    }

    FrameMetrics {
        id: metricsMain
        thread: FrameMetrics.Thread.Main
    }

    FrameMetrics {
        id: metricsRender
        thread: FrameMetrics.Thread.Render
    }

    Column {
        Text {
            text: {
                return "Main\n" +
                    "Current: " + metricsMain.fpsCurrent.toFixed(1) + "\n" +
                    "Rolling: " + metricsMain.fpsRolling.toFixed(1) + "\n" +
                    "Mean: " + metricsMain.fpsMean.toFixed(1) + "\n" +
                    "Min: " + metricsMain.fpsMin.toFixed(1) + "\n" + 
                    "Max: " + metricsMain.fpsMax.toFixed(1) + "\n" +
                    "Frame Count: " + metricsMain.frameCount.toFixed(1) + "\n" +
                    "====================";
            }

            color: "white"
        }

        Text {
            text: {
                return "Render\n" + 
                    "Current: " + metricsRender.fpsCurrent.toFixed(1) + "\n" +
                    "Rolling: " + metricsRender.fpsRolling.toFixed(1) + "\n" +
                    "Mean: " + metricsRender.fpsMean.toFixed(1) + "\n" +
                    "Min: " + metricsRender.fpsMin.toFixed(1) + "\n" + 
                    "Max: " + metricsRender.fpsMax.toFixed(1) + "\n" +
                    "Frame Count: " + metricsRender.frameCount.toFixed(1);
            }

            color: "white"
        }
    }
}
