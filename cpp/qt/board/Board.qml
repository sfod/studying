import QtQuick 2.0

Rectangle {
    id: board
    signal boardSignal(int idx)

    function addPawn(idx) {
        var pawn = Qt.createQmlObject('import QtQuick 2.2; DragTile {}', grid, "dynPawn")
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

