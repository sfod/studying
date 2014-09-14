import QtQuick 2.0

Item {
    Row {
        Rectangle {
            width: 30
            height: 30
            color: "black"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    carousel.decrementCurrentIndex()
                }
            }
        }

        Rectangle {
            width: 130
            height: 30

            Component {
                id: delegate
                Column {
                    id: wrapper
                    Text {
                        id: nameText
                        text: name
                        font.pointSize: 16
                        color: wrapper.PathView.isCurrentItem ? "black" : "transparent"
                    }
                }
            }

            PathView {
                id: carousel
                focus: true

                Keys.onLeftPressed: decrementCurrentIndex()
                Keys.onRightPressed: incrementCurrentIndex()

                anchors.fill: parent
                model: ListModel {
                    ListElement {
                        name: "human"
                    }
                    ListElement {
                        name: "AI"
                    }
                }
                delegate: delegate
                path: Path {
                    startX: 65
                    startY: 15
                    PathLine { relativeX: 0.1; relativeY: 0 }
                }
            }
        }

        Rectangle {
            width: 30
            height: 30
            color: "black"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    carousel.incrementCurrentIndex()
                }
            }
        }
    }
}
