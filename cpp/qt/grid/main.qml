import QtQuick 2.2
import QtQuick.Window 2.0

Window {
    visible: true

    width: 800
    height: 700

    Rectangle {
        id: rect

        property bool wallEnbled: true

        width: 500
        height: 500

        x: 100
        y: 50

        color: "#D18B47"

        function addPawn(idx) {
            var pawn = Qt.createQmlObject('import QtQuick 2.2; DragTile { initParent: repeater.itemAt(' + idx + ') }', pawnGrid, "dynPawn");
        }

        MouseArea {
            id: rectMouseArea

            property var tempWall
            property int tempWallX: -1
            property int tempWallY: -1

            anchors.fill: parent
            hoverEnabled: true

            function getWall(x, y) {
                var iw = pawnGrid.cellWidth + pawnGrid.lineWidth;
                var sx = Math.floor((x - pawnGrid.lineWidth) / iw);
                var px = (x - pawnGrid.lineWidth - sx * iw) / pawnGrid.cellWidth;

                var ih = pawnGrid.cellHeight + pawnGrid.lineWidth;
                var sy = Math.floor((y - pawnGrid.lineWidth) / ih);
                var py = (y - pawnGrid.lineWidth - sy * ih) / pawnGrid.cellHeight;

                var info = [];

                /* mouse cursor placed between nodes */
                if (py > 1.0) {
                    info = getHorizontalWallCoordinates(sx, px, sy, py);
                }
                /* mouse cursor placed between nodes */
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
                if (wallColumn == pawnGrid.columnNumber - 1) {
                    wallColumn -= 1;
                }
                else if (wallColumn == pawnGrid.columnNumber) {
                    wallColumn -= 2;
                }

                var wallRow = sy + Math.round(py);
                if (wallRow == 0) {
                    wallRow += 1;
                }
                if (wallRow == pawnGrid.rowNumber) {
                    wallRow -= 1;
                }

                return [0, wallRow, wallColumn, pawnGrid.rowNumber - wallRow, wallColumn];
            }

            function getVerticalWallCoordinates(sx, px, sy, py) {
                var wallColumn = sx + Math.round(px);
                if (wallColumn == 0) {
                    wallColumn += 1;
                }
                else if (wallColumn == pawnGrid.columnNumber) {
                    wallColumn -= 1;
                }

                var wallRow = sy + Math.floor(py) - 1;
                if (wallRow == -1) {
                    wallRow = 0;
                }
                if (wallRow == pawnGrid.rowNumber - 1) {
                    wallRow -= 1;
                }

                return [1, wallRow, wallColumn, pawnGrid.rowNumber - wallRow - 2, wallColumn];
            }

            onPositionChanged: {
                if (rect.wallEnbled) {
                    var wallInfo = getWall(mouseX, mouseY);

                    var alignment = wallInfo[0];
                    var wallRow = wallInfo[1];
                    var wallColumn = wallInfo[2];

                    var iw = pawnGrid.cellWidth + pawnGrid.lineWidth;

                    var wallX = -1;
                    var wallY = -1;
                    var wallWidth = -1;
                    var wallHeight = -1;
                    if (alignment) {
                        wallX = wallColumn * iw;
                        wallY = pawnGrid.lineWidth + wallRow * iw;
                        wallWidth = pawnGrid.lineWidth;
                        wallHeight = pawnGrid.lineWidth + 2 * pawnGrid.cellWidth;
                    }
                    else {
                        wallX = pawnGrid.lineWidth + wallColumn * iw;
                        wallY = wallRow * iw;
                        wallWidth = pawnGrid.lineWidth + 2 * pawnGrid.cellWidth;
                        wallHeight = pawnGrid.lineWidth;
                    }

                    if ((wallX != rectMouseArea.tempWallX) || (wallY != rectMouseArea.tempWallY)) {
                        if (rectMouseArea.tempWall) {
                            rectMouseArea.tempWall.destroy();
                        }
                        rectMouseArea.tempWall = Qt.createQmlObject(
                                'import QtQuick 2.2; ' + 'Rectangle { x: '
                                    + wallX + '; y: ' + wallY + '; width: '
                                    + wallWidth + '; height: ' + wallHeight
                                    + '; color: "brown" }',
                                rect, "wallLine");
                        rectMouseArea.tempWallX = wallX;
                        rectMouseArea.tempWallY = wallY;
                    }
                }
            }
        }

        Grid {
            id: pawnGrid

            property int lineWidth: 10
            property int cellWidth: 0
            property int cellHeight: 0
            property int columnNumber: 5
            property int rowNumber: 5

            width: parent.width - lineWidth * 2
            height: parent.height - lineWidth * 2
            x: lineWidth
            y: lineWidth

            rows: rowNumber
            columns: columnNumber

            spacing: lineWidth

            Repeater {
                id: repeater
                model: parent.rows * parent.columns
                delegate: DropTile {}
            }

            Component.onCompleted: {
                pawnGrid.cellWidth = repeater.itemAt(1).width;
                pawnGrid.cellHeight = repeater.itemAt(1).height;
                rect.addPawn(2);
                rect.addPawn(9);
            }
        }
    }

    Rectangle {
        id: stock

        x: 100
        y: parent.height - 100

        width: parent.width - 200
        height: 50

        color: "grey"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rect.wallEnbled = !rect.wallEnbled;
            }
        }
    }

}
