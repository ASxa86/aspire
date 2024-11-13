import QtQuick
import QtQuick.Layouts
import aspire
import app.edh

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    visibility: Qt.platform.os == "android" ? Window.FullScreen : Window.AutomaticVisibility
    color: "#1c1304"
    title: "EDH"

    ModelPlayers {
        id: player
    }

    GridLayout {
        id: layout
        anchors.fill: parent
        columns: 2
        rows: 2
        columnSpacing: parent.width / 24

        Repeater {
            id: repeater

            model: player

            delegate: Item {
                id: item

                Layout.fillHeight: true
                Layout.fillWidth: true

                // required property int index
                // required property color color
                // required property bool selected
                // required property int life

                rotation: index < layout.rows == 0 ? 0 : 180
                clip: true

                Rectangle {
                    id: mask
                    anchors.fill: parent
                    radius: width / 16
                    visible: false
                    layer.enabled: true
                }

                Rectangle {
                    id: glow
                    anchors.fill: parent
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        blurEnabled: true
                        blur: 0.7
                        brightness: 0.5
                    }

                    radius: width / 16
                    color: Style.color.verydarkyellow
                    scale: 0.94
                    opacity: selected ? 1 : 0

                    TapHandler {
                        onLongPressed: {
                            Actions.select(index);
                        }
                    }
                }

                Item {
                    anchors.fill: parent
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        source: counter
                        maskSource: mask
                        maskEnabled: true
                    }

                    scale: 0.93

                    Counter {
                        id: counter
                        anchors.fill: parent

                        color: background

                        gradient: Gradient {
                            GradientStop { position: 0.0; color: background }
                            GradientStop { position: 1.0; color: Qt.darker(background, 2.0) }
                        }


                        text: life.toString()
                        textTime: Qt.formatTime(new Date(time * 1000), "mm:ss")
                        active: selected

                        onDecrementClicked: {
                            Actions.updateLife(index, life - 1);
                        }

                        onIncrementClicked: {
                            Actions.updateLife(index, life + 1);
                        }

                        onTimeTriggered: (seconds) => {
                            Actions.updateTime(index, time + seconds);
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: shade
        anchors.fill: parent
        color: Qt.rgba(0.64, 0.64, 0.64, 0.5)
        visible: false

        TapHandler {
            gesturePolicy: TapHandler.WithinBounds

            onTapped: {
                shade.visible = false;
            }
        }
    }

    Column {
        id: menu
        anchors.centerIn: parent

        property point center: Qt.point(width / 2, height / 2)
        property int count: children.length
        spacing: window.height / count

        Item {
            width: window.width / 24
            height: width

            ImageSVG {
                id: refresh
                source: Icons.refresh
                color: "white"

                anchors.fill: parent

                property point center: Qt.point(width / 2, height / 2)

                NumberAnimation {
                    id: animForward
                    target: refresh
                    property: "rotation"
                    from: 0
                    to: 360
                    duration: 350
                }

                NumberAnimation {
                    id: animReverse
                    target: refresh
                    property: "rotation"
                    from: 360
                    to: 0
                    duration: 350
                }

                TapHandler {
                    gesturePolicy: TapHandler.WithinBounds
                    
                    onTapped: {
                        shade.visible = !shade.visible;
                    }
                }

                Connections {
                    target: shade
                    function onVisibleChanged() {
                        if(shade.visible == true) {
                            animForward.start();
                        }
                        else{
                            animReverse.start();
                        }
                    }
                }
            }

            Repeater {
                id: rptrReset
                model: 5
                delegate: Rectangle {
                    id: rect
                    width: refresh.width
                    height: width
                    color: "transparent"
                    visible: false

                    property double angle: index * (360.0 / rptrReset.count) - 90
                    property double rad: angle * Math.PI / 180
                    property double r: refresh.width * 2
                    x: refresh.center.x + r * Math.cos(rad) - rect.width / 2
                    y: refresh.center.y + r * Math.sin(rad) - rect.height / 2

                    NumberAnimation {
                        id: animForward
                        target: rect
                        property: "r"
                        from: 0
                        to: refresh.width * 2
                        duration: 350
                    }

                    NumberAnimation {
                        id: animReverse
                        target: rect
                        property: "r"
                        from: refresh.width * 2
                        to: 0
                        duration: 350

                        onFinished: {
                            rect.visible = false;
                        }
                    }

                    Connections {
                        target: shade

                        function onVisibleChanged() {
                            if(shade.visible == true) {
                                rect.visible = true;
                                animForward.start();
                            }
                            else
                            {
                                animReverse.start();
                            }
                        }
                    }

                    ImageSVG {
                        anchors.fill: parent
                        source: Icons.heart_filled
                        color: {
                            if(index == 0) {
                                return Style.color.verydarkyellow;
                            }

                            if(index == 1) {
                                return Style.color.verydarkblue;
                            }

                            if(index == 2) {
                                return Style.color.verydarkblack;
                            }

                            if(index == 3) {
                                return Style.color.verydarkred;
                            }

                            return Style.color.verydarkgreen;
                        }

                        TextEDH {
                            id: text

                            text: (index + 1) * 10
                            font.pointSize: 20
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter

                            anchors.fill: parent

                            TapHandler {
                                onTapped: {
                                    Actions.reset(parseInt(text.text));
                                    shade.visible = false;
                                }
                            }
                        }
                    }
                }
            }
        }

        ImageSVG {
            source: Icons.home
            color: "white"

            width: window.width / 24
            height: width
        }
    }

    FrameMetrics {
        id: metric
        thread: FrameMetrics.Thread.Render
    }

    Text {
        text: "FPS: " + metric.fpsRolling.toFixed(0)
        color: "white"
        font.pixelSize: Math.min(window.width, window.height) / 16
        visible: Qt.platform.os !== "android"
    }
}
