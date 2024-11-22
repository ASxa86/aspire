pragma Singleton
import QtQuick

QtObject {
    id: action

    signal reset(int life)

    signal updateLife(int index, int life)

    signal updateTime(int index, int seconds)

    signal select(int index)

    signal setPlayerTotal(int total)
}