import QtQuick

QtObject {
    id: subscribe

    required property AppState state
    required property Action action

    property Connections connection: Connections {
        target: subscribe.state

        function onCircleChanged(x) {
            subscribe.action.rotationChanged(x);
        }
    }
}