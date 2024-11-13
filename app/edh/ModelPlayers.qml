import QtQuick

ListModel {
    id: player

    ListElement {
        background: "darkred"
        selected: false
        life: 40
        time: 0
    }

    ListElement {
        background: "olivedrab"
        selected: false
        life: 40
        time: 0
    }

    ListElement {
        background: "darkcyan"
        selected: false
        life: 40
        time: 0
    }

    ListElement {
        background: "darkslategrey"
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