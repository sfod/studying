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
            onPositionChanged: {
                if (rect.wallEnbled) {
                    console.log("X is " + mouseX + ", Y is " + mouseY);

                    var alignment = -1;

                    var iw = pawnGrid.cellWidth + pawnGrid.lineWidth;
                    var sx = Math.floor((mouseX - pawnGrid.lineWidth) / iw);
                    var px = (mouseX - pawnGrid.lineWidth - sx * iw) / pawnGrid.cellWidth;

                    var ih = pawnGrid.cellHeight + pawnGrid.lineHeight;
                    var sy = Math.floor((mouseY - pawnGrid.lineHeight) / ih);
                    var py = (mouseY - pawnGrid.lineHeight - sy * ih) / pawnGrid.cellHeight;

                    if (py > 1.0) {
                        alignment = 0;
                    }
                    else if (px > 1.0) {
                        alignment = 1;
                    }
                    else {
                        var minPx = Math.min(Math.abs(1.0 - px), px);
                        var minPy = Math.min(Math.abs(1.0 - py), py);
                        alignment = minPy <= minPx ? 0 : 1;
                    }

                    var wallRow = -1;
                    var wallColumn = -1;
                    if (alignment) {
                        wallColumn = sx + Math.round(px);
                        if (wallColumn == 0) {
                            wallColumn += 1;
                        }
                        else if (wallColumn == pawnGrid.columnNumber) {
                            wallColumn -= 1;
                        }

                        wallRow = sy + Math.floor(py) - 1;
                        console.log("wall row is " + wallRow);
                        if (wallRow == -1) {
                            wallRow = 0;
                        }
                        if (wallRow == pawnGrid.rowNumber - 1) {
                            wallRow -= 1;
                        }
                    }
                    else {
                        wallColumn = sx + Math.floor(px);
                        if (wallColumn == pawnGrid.columnNumber - 1) {
                            wallColumn -= 1;
                        }
                        else if (wallColumn == pawnGrid.columnNumber) {
                            wallColumn -= 2;
                        }

                        wallRow = sy + Math.round(py);
                        if (wallRow == 0) {
                            wallRow += 1;
                        }
                        if (wallRow == pawnGrid.rowNumber) {
                            wallRow -= 1;
                        }
                    }

                    console.log("x: " + px + ", y: " + py);
                    var al = alignment ? "vertical" : "horizontal";
                    console.log(al + " wall: " + wallRow + ":" + wallColumn);

                    var wallX = -1;
                    var wallY = -1;
                    if (alignment) {
                        wallX = wallColumn * iw;
                        wallY = pawnGrid.lineWidth + wallRow * iw;
                        if ((wallX != rectMouseArea.tempWallX) || (wallY != rectMouseArea.tempWallY)) {
                            if (rectMouseArea.tempWall) {
                                rectMouseArea.tempWall.destroy();
                            }
                            rectMouseArea.tempWall = Qt.createQmlObject(
                                        'import QtQuick 2.2; '
                                        + 'Rectangle { x: ' + wallX + '; y: ' + wallY
                                        + '; width: ' + pawnGrid.lineWidth + '; height: '
                                        + (pawnGrid.lineWidth + 2 * pawnGrid.cellWidth) + '; color: "blue" }',
                                        rect, "wallLine");
                            rectMouseArea.tempWallX = wallX;
                            rectMouseArea.tempWallY = wallY;
                        }
                    }
                    else {
                        wallX = pawnGrid.lineWidth + wallColumn * iw;
                        wallY = wallRow * iw;
                        if ((wallX != rectMouseArea.tempWallX) || (wallY != rectMouseArea.tempWallY)) {
                            if (rectMouseArea.tempWall) {
                                rectMouseArea.tempWall.destroy();
                            }
                            rectMouseArea.tempWall = Qt.createQmlObject(
                                        'import QtQuick 2.2; '
                                        + 'Rectangle { x: ' + wallX + '; y: ' + wallY
                                        + '; width: ' + (pawnGrid.lineWidth + 2 * pawnGrid.cellWidth) + '; height: '
                                        + pawnGrid.lineWidth + '; color: "blue" }',
                                        rect, "wallLine");
                            rectMouseArea.tempWallX = wallX;
                            rectMouseArea.tempWallY = wallY;
                        }

                    }
                }
            }
        }

        Grid {
            id: pawnGrid

            property int lineWidth: 10
            property int lineHeight: lineWidth
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
                model: 25
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
