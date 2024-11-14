pragma Singleton
import QtQuick

QtObject {
    property FontLoader davidlibre: FontLoader {
        source: Fonts.davidlibre_regular
    }

    property QtObject color: QtObject {
        // Colors used for the background of the mana symbol.
        property color mountainBG: "#EB9F82"
        property color forestBG: "#C4D3CA"
        property color plainsBG: "#F8E7B9"
        property color islandBG: "#B3CEEA"
        property color swampBG: "#A69F9D"
        property color cardbackBG: "#B96E2A"

        property color lightmountainBG: Qt.lighter(mountainBG)
        property color lightforestBG: Qt.lighter(forestBG)
        property color lightplainsBG: Qt.lighter(plainsBG)
        property color lightislandBG: Qt.lighter(islandBG)
        property color lightswampBG: Qt.lighter(swampBG)
        property color lightcardbackBG: Qt.lighter(cardbackBG)

        property color darkmountainBG: Qt.darker(mountainBG)
        property color darkforestBG: Qt.darker(forestBG)
        property color darkplainsBG: Qt.darker(plainsBG)
        property color darkislandBG: Qt.darker(islandBG)
        property color darkswampBG: Qt.darker(swampBG)
        property color darkcardbackBG: Qt.darker(cardbackBG)

        // Colors used for the mana symbol.
        property color mountain: "#D32018"
        property color forest: "#00733E"
        property color plains: "#F9FAF4"
        property color island: "#0E68AB"
        property color swamp: "#150B00"
        property color cardback: "#361915"

        property color lightmountain: Qt.lighter(mountain)
        property color lightforest: Qt.lighter(forest)
        property color lightplains: Qt.lighter(plains)
        property color lightisland: Qt.lighter(island)
        property color lightswamp: Qt.lighter(swamp)
        property color lightback: Qt.lighter(cardback)

        property color darkmountain: Qt.darker(mountain)
        property color darkforest: Qt.darker(forest)
        property color darkplains: Qt.darker(plains)
        property color darkisland: Qt.darker(island)
        property color darkswamp: Qt.darker(swamp)
        property color darkcardback: Qt.darker(cardback)
    }
}