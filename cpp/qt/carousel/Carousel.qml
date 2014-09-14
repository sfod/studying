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
                        name: "Bill Jones"
                    }
                    ListElement {
                        name: "Jane Doe"
                    }
                    ListElement {
                        name: "John Smith"
                    }
                    ListElement {
                        name: "Some Name"
                    }
                }
                delegate: delegate
                path: Path {
                    startX: 65
                    startY: 15
                    PathLine { x: 65; y: 14 }
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
