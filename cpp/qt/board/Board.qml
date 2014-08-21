import QtQuick 2.0

Rectangle {
    id: board
    signal boardSignal(int idx)

    color: "#D18B47"

    Grid {
        columns: 9
        rows: 9
        width: parent.width - 10
        height: parent.height - 10
        x: 5
        y: 5
        spacing: 5

        Repeater {
            model: 81
            Rectangle {
                width: (parent.width - 40) / 9
                height: (parent.height - 40) / 9
                color: "#FFCE9E"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        board.boardSignal(index)
                    }
                }
            }
        }
    }
}

