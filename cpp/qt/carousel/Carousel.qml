import QtQuick 2.0

Rectangle {
    x: 100
    y: 200
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
