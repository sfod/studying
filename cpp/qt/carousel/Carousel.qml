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
                Item {
                    id: wrapper
                    anchors.fill: parent
                    Text {
                        id: nameText
                        text: name

                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        font.pointSize: 16
                        color: "black"
                        visible: wrapper.PathView.isCurrentItem ? true : false
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
                    startX: 0
                    startY: 0
                    PathLine { relativeX: 0; relativeY: 0 }
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
