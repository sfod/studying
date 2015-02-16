import QtQuick 2.0

Rectangle {
    id: board
    signal pawnDropped(int actorId, int idx)

    property var pawnList: ({})
    property bool isRunning: false
    property bool wallEnabled: true

    function init() {
        clear();
        start();
        console.log("initialized game");
    }

    function addPawn(actorId) {
        var component = Qt.createComponent("DragTile.qml");
        if (component.status === Component.Error) {
            console.log("error creating pawn: " + component.errorString());
        }
        var pawn = component.createObject(boardGrid, {actorId: actorId, visible: false});
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

    function setPawnPossibleMoves(actorId, possibleMoves) {
        if (isRunning && pawnList.hasOwnProperty(actorId)) {
            var pawn = pawnList[actorId];
            var moves = {};
            for (var i in possibleMoves) {
                moves[possibleMoves[i]] = 1;
            }
            pawn.setPossibleMoves(moves);
        }
    }

    function setPawnDragging(actorId, b) {
        if (isRunning) {
            var pawn = pawnList[actorId];
            pawn.setDragging(b);
        }
    }

    function finishGame() {
        for (var i in pawnList) {
            pawnList[i].setDragging(false);
        }
        stop();
    }

    function endGame() {
        clear();
        stop();
    }

    function clear() {
        for (var i in pawnList) {
            pawnList[i].destroy();
        }
        pawnList = {};
    }

    function start() {
        isRunning = true;
    }

    function stop() {
        isRunning = false;
    }

    color: "#D18B47"

    MouseArea {
        id: boardMouseArea

        property var tempWall
        property int tempWallX: -1
        property int tempWallY: -1

        anchors.fill: parent
        hoverEnabled: true

        function getWall(x, y) {
            var iw = boardGrid.cellWidth + boardGrid.lineWidth;
            var sx = Math.floor((x - boardGrid.lineWidth) / iw);
            var px = (x - boardGrid.lineWidth - sx * iw) / boardGrid.cellWidth;

            var ih = boardGrid.cellHeight + boardGrid.lineWidth;
            var sy = Math.floor((y - boardGrid.lineWidth) / ih);
            var py = (y - boardGrid.lineWidth - sy * ih) / boardGrid.cellHeight;

            var info = [];

            /* mouse cursor placed on line between nodes */
            if (py > 1.0) {
                info = getHorizontalWallCoordinates(sx, px, sy, py);
            }
            /* mouse cursor placed on line between nodes */
            else if (px > 1.0) {
                info = getVerticalWallCoordinates(sx, px, sy, py);
            }
            else {
                var minPx = Math.min(Math.abs(1.0 - px), px);
                var minPy = Math.min(Math.abs(1.0 - py), py);
                if (minPy <= minPx) {
                    info = getHorizontalWallCoordinates(sx, px, sy, py);
                }
                else {
                    info = getVerticalWallCoordinates(sx, px, sy, py);
                }
            }

            return info;
        }

        function getHorizontalWallCoordinates(sx, px, sy, py) {
            var wallColumn = sx + Math.floor(px);
            if (wallColumn == boardGrid.columnNumber - 1) {
                wallColumn -= 1;
            }
            else if (wallColumn == boardGrid.columnNumber) {
                wallColumn -= 2;
            }

            var wallRow = sy + Math.round(py);
            if (wallRow == 0) {
                wallRow += 1;
            }
            if (wallRow == boardGrid.rowNumber) {
                wallRow -= 1;
            }

            return [0, wallRow, wallColumn, boardGrid.rowNumber - wallRow, wallColumn];
        }

        function getVerticalWallCoordinates(sx, px, sy, py) {
            var wallColumn = sx + Math.round(px);
            if (wallColumn == 0) {
                wallColumn += 1;
            }
            else if (wallColumn == boardGrid.columnNumber) {
                wallColumn -= 1;
            }

            var wallRow = sy + Math.floor(py) - 1;
            if (wallRow == -1) {
                wallRow = 0;
            }
            if (wallRow == boardGrid.rowNumber - 1) {
                wallRow -= 1;
            }

            return [1, wallRow, wallColumn, boardGrid.rowNumber - wallRow - 2, wallColumn];
        }

        onPositionChanged: {
            if (board.wallEnabled) {
                var wallInfo = getWall(mouseX, mouseY);

                var alignment = wallInfo[0];
                var wallRow = wallInfo[1];
                var wallColumn = wallInfo[2];

                var iw = boardGrid.cellWidth + boardGrid.lineWidth;
                var ih = boardGrid.cellHeight + boardGrid.lineWidth;

                var wallX = -1;
                var wallY = -1;
                var wallWidth = -1;
                var wallHeight = -1;
                if (alignment) {
                    wallX = wallColumn * iw;
                    wallY = boardGrid.lineWidth + wallRow * ih;
                    wallWidth = boardGrid.lineWidth;
                    wallHeight = boardGrid.lineWidth + 2 * boardGrid.cellHeight;
                }
                else {
                    wallX = boardGrid.lineWidth + wallColumn * iw;
                    wallY = wallRow * ih;
                    wallWidth = boardGrid.lineWidth + 2 * boardGrid.cellWidth;
                    wallHeight = boardGrid.lineWidth;
                }

                if ((wallX != boardMouseArea.tempWallX) || (wallY != boardMouseArea.tempWallY)) {
                    if (boardMouseArea.tempWall) {
                        boardMouseArea.tempWall.destroy();
                    }
                    boardMouseArea.tempWall = Qt.createQmlObject(
                            'import QtQuick 2.2; ' + 'Rectangle { x: '
                                + wallX + '; y: ' + wallY + '; width: '
                                + wallWidth + '; height: ' + wallHeight
                                + '; color: "blue" }',
                            board, "wallLine");
                    boardMouseArea.tempWallX = wallX;
                    boardMouseArea.tempWallY = wallY;
                }
            }
        }
    }

    Grid {
        id: boardGrid

        property int lineWidth: 5
        property real cellWidth: 0
        property real cellHeight: 0
        property int columnNumber: 9
        property int rowNumber: 9

        rows: rowNumber
        columns: columnNumber

        width: parent.width - lineWidth * 2
        height: parent.height - lineWidth * 2
        x: lineWidth
        y: lineWidth

        spacing: lineWidth

        Repeater {
            id: repeater
            width: parent.width
            height: parent.height

            model: parent.rows * parent.columns
            delegate: DropTile {}
        }

        Component.onCompleted: {
            boardGrid.cellWidth = repeater.itemAt(1).width;
            boardGrid.cellHeight = repeater.itemAt(1).height;
        }
    }
}
