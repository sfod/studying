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
        width: parent.width - 10
        height: parent.height - 10
        x: 5
        y: 5
        spacing: 5

        Repeater {
            id: repeater
            model: parent.rows * parent.columns
            delegate: DropTile {}
        }
    }
}

