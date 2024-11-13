pragma Singleton
import QtQuick

QtObject {
    id: action

    signal reset(int life)

    signal updateLife(int index, int life)

    signal select(int index)
}