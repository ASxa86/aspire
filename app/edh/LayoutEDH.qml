import QtQuick
import QtQuick.Layouts

Item {
    id: root

    readonly property int columns: 2
    readonly property int rows: 2
    property int spacing: 2
    property int count: 4

    required property Component delegate

    onCountChanged: updateCount();
    onChildrenChanged: updateLayout();
    onWidthChanged: updateLayout()
    onHeightChanged: updateLayout()
    onSpacingChanged: updateLayout()
    Component.onCompleted: updateCount();

    function updateCount() {
        if(root.delegate === null) {
            return;
        }

        for(let i = 0; i < root.children.length; i++) {
            root.children[i].destroy();
        }

        for(let i = 0; i < root.count; i++) {
            root.delegate.createObject(root, {x: 0, y: 0, width: 0, height: 0});
        }
    }

    function updateLayout() {
        for(let i = 0; i < root.children.length; i++) {
            let cell = calcCell(i);
            let item = root.children[i];
            item.x = cell.x;
            item.y = cell.y;
            item.width = cell.width;
            item.height = cell.height;
        }
    }

    function calcCell(index) {
        const maxColumns = root.columns;
        const maxRows = Math.ceil(Math.max(root.rows, root.count / root.columns));

        let column = index % maxColumns;
        let row = root.count > 2 ? Math.floor(index / maxColumns) : index;

        // For 1 count, consume the whole size of the containing item.
        let cellX = 0;
        let cellY = 0;
        let cellWidth = root.width;
        let cellHeight = root.height;

        if(root.count >= 2) {
            // All items' heights will be relative to the number of rows in the grid.
            cellHeight = (cellHeight - (root.spacing * (maxRows - 1))) / maxRows;
            cellY = row * (cellHeight + root.spacing);

            // Only change the width from the maximum width if we aren't the last item of an uneven count.
            // Otherwise, the last item will remain the maximum width of the grid.
            if(root.count % 2 === 0 || index !== root.count - 1) {
                cellWidth = (cellWidth - (root.spacing * maxColumns - 1)) / maxColumns;
                cellX = column * (cellWidth + (root.spacing * maxColumns - 1));
            }
        }

        return { x: cellX, y: cellY, width: cellWidth, height: cellHeight };
    }
}
