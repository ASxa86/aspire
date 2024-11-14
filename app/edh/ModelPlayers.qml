import QtQuick

ListModel {
    id: player

    ListElement {
        background: "#D32018"
        selected: false
        life: 40
        time: 0
    }

    ListElement {
        background: "#00733E"
        selected: false
        life: 40
        time: 0
    }

    ListElement {
        background: "#0E68AB"
        selected: false
        life: 40
        time: 0
    }

    ListElement {
        background: "#F8E7B9"
        selected: false
        life: 40
        time: 0
    }

    property Connections connection: Connections {
        target: Actions

        function onReset(x) {
            for(let i = 0; i < player.count; i++) {
                player.set(i, {life: x});
            }
        }

        function onSelect(index) {
            for(let i = 0; i < player.count; i++) {
                player.set(i, {selected: false});
            }

            player.set(index, {selected: true});
        }

        function onUpdateLife(index, x) {
            player.set(index, {life: x});
        }

        function onUpdateTime(index, x) {
            player.set(index, {time: x});
        }
    }
}