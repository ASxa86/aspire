pragma Singleton
import QtQuick

QtObject {
    readonly property FontLoader davidlibre: FontLoader {
        source: Fonts.davidlibre_regular
    }

    readonly property real inchesPerMeter: 39.3701
    readonly property real pixelsPerInch: Screen.pixelDensity * inchesPerMeter
    readonly property real iconSize: 0.25 * pixelsPerInch

    property QtObject color: QtObject {
        // Colors used for the background of the mana symbol.
        readonly property color mountainBG: "#EB9F82"
        readonly property color forestBG: "#C4D3CA"
        readonly property color plainsBG: "#F8E7B9"
        readonly property color islandBG: "#B3CEEA"
        readonly property color swampBG: "#A69F9D"
        readonly property color cardbackBG: "#B96E2A"

        readonly property color lightmountainBG: Qt.lighter(mountainBG)
        readonly property color lightforestBG: Qt.lighter(forestBG)
        readonly property color lightplainsBG: Qt.lighter(plainsBG)
        readonly property color lightislandBG: Qt.lighter(islandBG)
        readonly property color lightswampBG: Qt.lighter(swampBG)
        readonly property color lightcardbackBG: Qt.lighter(cardbackBG)

        readonly property color darkmountainBG: Qt.darker(mountainBG)
        readonly property color darkforestBG: Qt.darker(forestBG)
        readonly property color darkplainsBG: Qt.darker(plainsBG)
        readonly property color darkislandBG: Qt.darker(islandBG)
        readonly property color darkswampBG: Qt.darker(swampBG)
        readonly property color darkcardbackBG: Qt.darker(cardbackBG)

        // Colors used for the mana symbol.
        readonly property color mountain: "#D32018"
        readonly property color forest: "#00733E"
        readonly property color plains: "#F9FAF4"
        readonly property color island: "#0E68AB"
        readonly property color swamp: "#150B00"
        readonly property color cardback: "#361915"

        readonly property color lightmountain: Qt.lighter(mountain)
        readonly property color lightforest: Qt.lighter(forest)
        readonly property color lightplains: Qt.lighter(plains)
        readonly property color lightisland: Qt.lighter(island)
        readonly property color lightswamp: Qt.lighter(swamp)
        readonly property color lightback: Qt.lighter(cardback)

        readonly property color darkmountain: Qt.darker(mountain)
        readonly property color darkforest: Qt.darker(forest)
        readonly property color darkplains: Qt.darker(plains)
        readonly property color darkisland: Qt.darker(island)
        readonly property color darkswamp: Qt.darker(swamp)
        readonly property color darkcardback: Qt.darker(cardback)
    }
}