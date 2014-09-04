import QtQuick 2.2
import QtQuick.Window 2.0

Window {
    visible: true

    width: 800
    height: 650

    Rectangle {
        id: rect

        width: 500
        height: 500

        x: 100
        y: 100

        color: "#D18B47"

        function addPawn(idx) {
            var pawn = Qt.createQmlObject('import QtQuick 2.2; DragTile { initParent: repeater.itemAt(' + idx + ') }', grid, "dynPawn")
        }

        Grid {
            id: grid

            width: parent.width - 10
            height: parent.height - 10
            x: 5
            y: 5

            rows: 5
            columns: 5

            spacing: 5

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
}
