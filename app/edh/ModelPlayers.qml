import QtQuick

ListModel {
    id: player

    Component.onCompleted: {
        player.append({
            background: Style.color.mountain,
            selected: false,
            life: 40,
            time: 0
        });

        player.append({
            background: Style.color.forest,
            selected: false,
            life: 40,
            time: 0
        });

        player.append({
            background: Style.color.island,
            selected: false,
            life: 40,
            time: 0
        });

        player.append({
            background: Style.color.plainsBG,
            selected: false,
            life: 40,
            time: 0
        });
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