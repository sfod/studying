import QtQuick 2.0

Rectangle {
    id: board
    signal pawnDropped(int actorId, int idx)

    property var pawnList: []

    function addPawn(actorId, idx) {
        var component = Qt.createComponent("DragTile.qml")
        var pawn = component.createObject(grid, {actorId: actorId, initParent: repeater.itemAt(idx)})

        pawnList.push(pawn)
    }

    function endGame() {
        for (var i in pawnList) {
            pawnList[i].destroy()
        }
        pawnList = []
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
