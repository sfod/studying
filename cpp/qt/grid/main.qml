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
                    var w = (pawnGrid.width - pawnGrid.lineWidth) / 5;
                    var i = (mouseX - pawnGrid.lineWidth) / w;
                    console.log("i is " + i);
                    var wallX = mouseX < 100 ? 0 : 100;
                    var wallY = 0;
                    console.log("nearest wall is: " + wallX + ":" + wallY);
                }
            }
        }

        Grid {
            id: pawnGrid

            property int lineWidth: 10

            width: parent.width - lineWidth * 2
            height: parent.height - lineWidth * 2
            x: lineWidth
            y: lineWidth

            rows: 5
            columns: 5

            spacing: lineWidth

            Repeater {
                id: repeater
                model: 25
                delegate: DropTile {}
            }

            Component.onCompleted: {
                rect.addPawn(2)
                rect.addPawn(9)
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
