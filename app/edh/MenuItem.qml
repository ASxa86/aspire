import QtQuick

Item {
    id: root

    property RadialMenu menu: null
    property RadialMenu subMenu: null
    property bool down: false

    signal pressed()
    signal released()
    signal toggled()
    signal triggered()

    function toggle() {
        root.down = !root.down;
    }

    onParentChanged: {
        if(root.parent instanceof RadialMenu) {
            root.menu = root.parent as RadialMenu;
        }
    }

    onDownChanged: {
        root.toggled();

        if(root.down === true) {
            root.triggered();
        }

        if(root.subMenu === null) {
            return;
        }

        if(root.down === true) {
            root.subMenu.open();
        }
        else {
            root.subMenu.close();
        }
    }

    TapHandler {
        id: handler

        gesturePolicy: TapHandler.WithinBounds
        longPressThreshold: 0
        onTapped: root.toggle()
        onPressedChanged: handler.pressed === true ? root.pressed() : root.released()
    }
}
