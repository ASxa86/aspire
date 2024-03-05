import QtQuick

QtObject {
    id: state

    property double rotate: 0.0

    signal circleChanged(double x)

    property Timer timer: Timer {
        id: timer
        running: true
        repeat: true
        interval: 10


        onTriggered: {
            state.rotate += interval / 1000.0;
            state.circleChanged(state.rotate);
        }
    }
}