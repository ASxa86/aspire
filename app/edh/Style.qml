pragma Singleton
import QtQuick

QtObject {
    property FontLoader davidlibre: FontLoader {
        source: Fonts.davidlibre_regular
    }

    property QtObject color: QtObject {
        property color lightblack: "#413A3B"
        property color lightred: "#D1604D"
        property color lightblue: "#9ECED1"
        property color lightgreen: "#D2DFCD"
        property color lightyellow: "#F8ECC9"
        property color lightwhite: "#FFFFFF"


        property color black: "#231F20"
        property color red: "#BB4430"
        property color blue: "#7EBDC2"
        property color green: "#B9CEB2"
        property color yellow: "#F3E0A5"
        property color white: "#EFE6DD"

        property color darkblack: "#161314"
        property color darkred: "#A23C2A"
        property color darkblue: "#66B2B7"
        property color darkgreen: "#A6BF9B"
        property color darkyellow: "#EED381"
        property color darkwhite: "#D6D6D6"

        property color verydarkblack: "#000000"
        property color verydarkred: "#622318"
        property color verydarkblue: "#346C6F"
        property color verydarkgreen: "#668958"
        property color verydarkyellow: "#B48D18"
        property color verydarkwhite: "#A3A3A3"
    }
}