import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 500
    height: 550
    title: qsTr("Quoridor")

    Rectangle {
        id: windowMain
        state: "stateMainMenu"

        width: parent.width
        height: parent.height
        x: 0
        y: 0

        // main menu window
        Item {
            id: windowMainMenu
            objectName: "mainMenu"

            x: 20
            y: 20
            width: parent.width - 40
            height: parent.height - 40

            onVisibleChanged: {
                if (visible == true) {
                }
            }

            Column {
                y: 100
                width: parent.width
                height: parent.height - 100
                spacing: 20

                Button {
                    id: buttonNewGame
                    objectName: "buttonNewGame"

                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "New Game"
                    onClicked: {
                        windowMain.state = "stateGame"
                    }
                }

                Button {
                    id: buttonQuit
                    objectName: "buttonQuit"

                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Quit"
                }
            }
        }

        // game window
        Item {
            id: windowGame
            objectName: "game"

            x: 20
            y: 20
            width: parent.width - 40
            height: parent.height - 40

            signal nodeClicked(int idx)
            signal backButtonClicked()

            Board {
                id: board

                width: parent.width
                height: parent.height - 40
                x: 0
                y: 0

                onBoardSignal: {
                    console.log("clicked " + idx + " node")
                    windowGame.nodeClicked(idx)
                }
            }

            Button {
                id: buttonBackToMainMenu
                objectName: "buttonBackToMainMenu"

                text: "Back"

                anchors.top: board.bottom

                onClicked: {
                    windowGame.backButtonClicked()
                    windowMain.state = "stateMainMenu"
                }
            }
        }

        states: [
            State {
                name: "stateMainMenu"
                PropertyChanges {
                    target: windowMainMenu
                    visible: true
                }
                PropertyChanges {
                    target: windowGame
                    visible: false
                }
            },
            State {
                name: "stateGame"
                PropertyChanges {
                    target: windowMainMenu
                    visible: false
                }
                PropertyChanges {
                    target: windowGame
                    visible: true
                }
            }
        ]
    }
}
