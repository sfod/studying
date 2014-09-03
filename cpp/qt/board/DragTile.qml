import QtQuick 2.0

Item {
    id: root

    width: (parent.width - (parent.columns - 1) * parent.spacing) / parent.columns
    height: (parent.height - (parent.rows - 1) * parent.spacing) / parent.rows
//    width: parent.width
//    height: parent.height

    MouseArea {
        id: mouseArea

        width: parent.width
        height: parent.height
        anchors.centerIn: parent

        drag.target: pawn.isDraggedEnable ? pawn : null
        onReleased: {
            if (pawn.isDraggedEnable) {
                parent = pawn.Drag.target !== null ? pawn.Drag.target : pawn.curParent
                pawn.curParent = parent
                pawn.Drag.drop()
            }
        }

        Rectangle {
            id: pawn
            color: "transparent"

            property bool isDraggedEnable: true
            property Item curParent: root

            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: parent.width / 2
            Drag.hotSpot.y: parent.height / 2

            Image {
                source: "resources/pawn.png"
                anchors.fill: parent
            }

            states: State {
                when: mouseArea.drag.active
                ParentChange { target: pawn; parent: root }
                AnchorChanges {target: pawn; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined}
            }
        }
    }
}
