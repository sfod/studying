import QtQuick 2.2
import QtQuick.Window 2.0

Window {
    visible: true

    width: 800
    height: 650

    Rectangle {
        width: 500
        height: 500

        x: 100
        y: 100

        color: "#D18B47"

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
                model: 25
                delegate: DropTile {}
            }

            DragTile {}
        }
    }
}
