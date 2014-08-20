import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("pages")

    Rectangle {
        id: mainWindow
        state: "mainMenu"

        width: parent.width
        height: parent.height
        x: 0
        y: 0

        // main menu window
        Rectangle {
            id: mainMenuWindow

            x: 20
            y: 20
            width: parent.width - 40
            height: parent.height - 40

            color: "grey"

            Component.onCompleted: console.log("main menu is ready")

            onVisibleChanged: {
                if (visible == true) {
                    console.log("main menu")
                }
            }

            Button {
                id: newGameButton
                text: "New Game"

                anchors.centerIn: parent

                onClicked: {
                    mainWindow.state = "newGame"
                }
            }
        }

        // new game window
        Rectangle {
            id: newGameWindow

            x: 20
            y: 20
            width: parent.width - 40
            height: parent.height - 40

            color: "grey"

            onVisibleChanged: {
                if (visible == true) {
                    console.log("new game")
                }
            }

            Button {
                id: backToMainMenuButton
                text: "Back"

                anchors.centerIn: parent

                onClicked: {
                    mainWindow.state = "mainMenu"
                }
            }
        }

        states: [
            State {
                name: "mainMenu"
                PropertyChanges {
                    target: mainMenuWindow
                    visible: true
                }
                PropertyChanges {
                    target: newGameWindow
                    visible: false
                }
            },
            State {
                name: "newGame"
                PropertyChanges {
                    target: mainMenuWindow
                    visible: false
                }
                PropertyChanges {
                    target: newGameWindow
                    visible: true
                }
            }
        ]
    }
}
