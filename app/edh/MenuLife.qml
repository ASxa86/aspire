import QtQuick

Item {
    ListModel {
        id: model

        Component.onCompleted: {
            model.append({
                life: 10,
                background: Style.color.plainsBG,
                foreground: Style.color.plains,
                outline: true
            });

            model.append({
                life: 20,
                background: Style.color.islandBG,
                foreground: Style.color.island,
                outline: false
            });

            model.append({
                life: 30,
                background: Style.color.swampBG,
                foreground: Style.color.swamp,
                outline: false
            });

            model.append({
                life: 40,
                background: Style.color.mountainBG,
                foreground: Style.color.mountain,
                outline: false
            });

            model.append({
                life: 50,
                background: Style.color.forestBG,
                foreground: Style.color.forest,
                outline: false
            });
        }
    }

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
        model: model
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
                color: background

                TextEDH {
                    id: text

                    text: life
                    style: outline == true ? Text.Outline : Text.Normal
                    color: foreground
                    font.pointSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    anchors.fill: parent

                    TapHandler {
                        onTapped: {
                            Actions.reset(life);
                            shade.visible = false;
                        }
                    }
                }
            }
        }
    }
}