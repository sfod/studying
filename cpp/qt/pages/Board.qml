import QtQuick 2.0

Rectangle {
    visible: true
    width: 500
    height: 550

    Rectangle {
        color: "#D18B47"
        width: parent.width - 20
        height: parent.height - 70
        x: 10
        y: 10

        Grid {
            id: board
            objectName: "board"

            signal boardSignal(int idx)

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
}
