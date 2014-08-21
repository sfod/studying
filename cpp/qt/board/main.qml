import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 500
    height: 550
    title: qsTr("Quoridor")

    Board {
        objectName: "board"
        width: parent.width - 20
        height: parent.height - 70
        x: 10
        y: 10
    }

    Button {
        objectName: "boardBack"

        x: 30
        y: parent.height - 40

        text: "back"
    }

}
