import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

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

            RowLayout {
                height: parent.height / 2
                width: parent.width
                anchors.bottom: parent.bottom

                Item {
                    anchors.left: parent.left
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Button {
                        id: buttonNewGame
                        objectName: "buttonNewGame"
                        text: "New Game"
                        anchors.centerIn: parent
                        onClicked: {
                            windowMain.state = "stateOptions"
                        }
                    }
                }

                Item {
                    anchors.right: parent.right
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Button {
                        id: buttonQuit
                        objectName: "buttonQuit"
                        text: "Quit"
                        anchors.centerIn: parent
                    }
                }
            }
        }

        // options window
        Item {
            id: windowOptions

            x: 20
            y: 20
            width: parent.width - 40
            height: parent.height - 40

            Options {}

            RowLayout {
                height: parent.height / 2
                width: parent.width
                anchors.bottom: parent.bottom

                Item {
                    anchors.left: parent.left
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Button {
                        id: buttonStartGame
                        objectName: "buttonStartGame"
                        text: "Start Game"
                        anchors.centerIn: parent
                        onClicked: {
                            windowMain.state = "stateGame"
                        }
                    }
                }

                Item {
                    anchors.right: parent.right
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Button {
                        id: buttonBackToMainMenu
                        objectName: "buttonBackToMainMenu"
                        text: "Back"
                        anchors.centerIn: parent
                        onClicked: {
                            windowMain.state = "stateMainMenu"
                        }
                    }
                }
            }
        }

        // game window
        Item {
            id: windowGame

            x: 20
            y: 20
            width: parent.width - 40
            height: parent.height - 40

            Board {
                id: board
                objectName: "board"

                width: parent.width
                height: parent.height - 40
                x: 0
                y: 0
            }

            Item {
                width: parent.width / 2
                anchors.top: board.bottom
                anchors.bottom: parent.bottom
                anchors.right: parent.right

                Button {
                    id: buttonBackToOptions
                    objectName: "buttonBackToOptions"
                    text: "Back"

                    anchors.centerIn: parent

                    onClicked: {
                        board.endGame()
                        windowMain.state = "stateOptions"
                    }
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
                    target: windowOptions
                    visible: false
                }
                PropertyChanges {
                    target: windowGame
                    visible: false
                }
            },
            State {
                name: "stateOptions"
                PropertyChanges {
                    target: windowMainMenu
                    visible: false
                }
                PropertyChanges {
                    target: windowOptions
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
                    target: windowOptions
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
