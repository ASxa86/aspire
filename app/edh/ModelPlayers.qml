import QtQuick

ListModel {
    id: model

    property var backgrounds: [
        Style.color.mountain,
        Style.color.forest,
        Style.color.island,
        Style.color.plainsBG,
        Style.color.swampBG,
        Style.color.lightcardbackBG
    ];

    property Connections connection: Connections {
        target: Actions

        function onReset(x) {
            for(let i = 0; i < model.count; i++) {
                model.set(i, {life: x});
                model.set(i, {time: 0});
                model.set(i, {selected: false});
            }
        }

        function onSelect(index) {
            for(let i = 0; i < model.count; i++) {
                model.set(i, {selected: false});
            }

            model.set(index, {selected: true});
        }

        function onUpdateLife(index, x) {
            model.set(index, {life: x});
        }

        function onUpdateTime(index, x) {
            model.set(index, {time: x});
        }

        function onSetPlayerTotal(total) {
            model.clear();
            
            for(let i = 0; i < total; i++) {
                model.append({
                    background: model.backgrounds[i % model.backgrounds.length],
                    selected: false,
                    life: 40,
                    time: 0
                });
            }
        }
    }
}