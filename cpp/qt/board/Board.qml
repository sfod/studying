import QtQuick 2.0

Rectangle {
    id: board
    signal pawnDropped(int actorId, int idx)

    property var pawnList: ({})

    function addPawn(actorId) {
        var component = Qt.createComponent("DragTile.qml");
        if (component.status === Component.Error) {
            console.log("error creating pawn: " + component.errorString());
        }
        var pawn = component.createObject(grid, {actorId: actorId, visible: false});
        pawn.setDragging(false);
        pawnList[actorId] = pawn;
    }

    function setPawnPos(actorId, idx, possibleMoves) {
        if (pawnList.hasOwnProperty(actorId)) {
            var pawn = pawnList[actorId];
            pawn.setParent(repeater.itemAt(idx));

            if (!pawn.visible) {
                pawn.visible = true;
            }

            console.log("set pawn on " + idx);

            var moves = {};
            for (var i in possibleMoves) {
                moves[possibleMoves[i]] = 1;
            }
            pawn.setPossibleMoves(moves);
        }
    }

    function setPawnDragging(actorId, b) {
        var pawn = pawnList[actorId];
        pawn.setDragging(b);
    }

    function endGame() {
        for (var i in pawnList) {
            pawnList[i].destroy();
        }
        pawnList = {};
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
