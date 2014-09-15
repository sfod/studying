import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
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

    ListModel {
        id: cm
        ListElement {
            name: "human"
        }
        ListElement {
            name: "AI"
        }
        ListElement {
            name: "network"
        }
    }


    Carousel {
        x: 100
        y: 100
        carouselModel: cm
    }
}
