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
            var pawn = Qt.createQmlObject('import QtQuick 2.2; DragTile { initParent: repeater.itemAt(' + idx + ') }', pawnGrid, "dynPawn")
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onPositionChanged: {
                if (rect.wallEnbled) {
                    console.log("X is " + mouseX + ", Y is " + mouseY);
                    var iw = pawnGrid.cellWidth + pawnGrid.lineWidth;
                    var ih = pawnGrid.cellHeight + pawnGrid.lineHeight;

                    var sx = Math.floor((mouseX - pawnGrid.lineWidth) / iw);
                    var px = (mouseX - pawnGrid.lineWidth - sx * iw) / pawnGrid.cellWidth;

                    var sy = Math.floor((mouseY - pawnGrid.lineHeight) / ih);
                    var py = (mouseY - pawnGrid.lineHeight - sy * ih) / pawnGrid.cellHeight;

                    var wallColumn = sx + Math.round(px);
                    if (wallColumn == 0) {
                        wallColumn += 1;
                    }
                    if (wallColumn == pawnGrid.columnNumber) {
                        wallColumn -= 1;
                    }

                    var wallRow = pawnGrid.rowNumber - (sy + Math.round(py));
                    if (wallRow == 0) {
                        wallRow += 1;
                    }
                    if (wallRow == pawnGrid.rowNumber) {
                        wallRow -= 1;
                    }

                    console.log("wall: " + wallRow + ":" + wallColumn);
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
