import QtQuick 2.0

DropArea {
    id: dragTarget

    width: (parent.width - (parent.columns - 1) * parent.spacing) / parent.columns
    height: (parent.height - (parent.rows - 1) * parent.spacing) / parent.rows

    onDropped: {
        console.log("dropped on " + index)
    }

    Rectangle {
        id: dropRectangle

        anchors.fill: parent
        color: "#FFCE9E"

        states: State {
            when: dragTarget.containsDrag
            PropertyChanges {
                target: dropRectangle
                color: "grey"
            }
        }
    }
}
