import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 500
    height: 500
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle {
        color: "#D18B47"
        width: parent.width - 20
        height: parent.height - 20
        x: 10
        y: 10

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
                            parent.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
                        }
                    }
                }
            }
        }
    }
}
