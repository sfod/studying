import QtQuick 2.0

Rectangle {
    id: board
    signal nodeClicked(int idx)

    function addPawn(idx) {
        var component = Qt.createComponent("DragTile.qml")
        var pawn = component.createObject(grid, {initParent: repeater.itemAt(idx)})
    }

    color: "#D18B47"

    Grid {
        id: grid

        columns: 9
        rows: 9

        width: parent.width - spacing * 2
        height: parent.height - spacing * 2
        x: spacing
        y: spacing

        spacing: 3

        Repeater {
            id: repeater
            model: parent.rows * parent.columns
            delegate: DropTile {}
        }
    }
}

