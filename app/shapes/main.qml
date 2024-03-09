import QtQuick
import aspire

Window {
    id: window
    title: "shapes"
    visible: true
    width: 1920
    height: 1080
    color: "black"

    AppState {
        id: state
    }

    Action {
        id: action
    }

    Subscribe {
        id: subscribe

        action: action
        state: state
    }

    Item {
        anchors.fill: parent

        WheelHandler {
            target: repeater
            orientation: Qt.Vertical
            property: "radius"
            rotationScale: 15
            acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
        }

        rotation: repeater.model.rotation

        Repeater {
            id: repeater

            model: ModelEntity {
                id: modelEntity
                count: 2000

                property Connections cx: Connections {
                    target: action

                    function onRotationChanged(rotation) {
                        modelEntity.rotation = rotation;
                    }
                }
            }

            property double radius: Math.min(window.width / 2, window.height / 2)

            delegate: Item {
                id: item
                x: parent.width / 2
                y: parent.height / 2
                enabled: false

                Rectangle {
                    id: rectangle

                    property double angle: Math.random() * 360 * Math.PI / 180
                    x: Math.cos(angle) * repeater.radius * Math.random()
                    y: Math.sin(angle) * repeater.radius * Math.random()
                    width: 32
                    height: 32
                    rotation: model.rotation - modelEntity.rotation
                    color: "black"
                    border.color: "green"
                    border.width: 2

                    Text {
                        anchors.fill: parent
                        anchors.centerIn: parent
                        text: model.id
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        renderType: Text.NativeRendering
                        // renderTypeQuality: Text.LowRenderTypeQuality
                        // antialiasing: false
                    }
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
            font.pixelSize: 30
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
            font.pixelSize: 30
        }
    }
}
