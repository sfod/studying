import QtQuick 2.0

Item {
    id: root

    width: 93
    height: 93

    MouseArea {
        id: mouseArea

        width: 93
        height: 93
        anchors.centerIn: parent

        drag.target: pawn.isDraggedEnable ? pawn : null
        onReleased: {
            if (pawn.isDraggedEnable) {
                parent = pawn.Drag.target !== null ? pawn.Drag.target : root
                pawn.Drag.drop()
            }
        }

        Rectangle {
            id: pawn
            color: "transparent"

            property bool isDraggedEnable: true

            width: 93
            height: 93
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 46
            Drag.hotSpot.y: 46

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
