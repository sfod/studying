import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    id: options

    property var playerNum: []
    property var playerTypes: []

    // @todo check for available player types
    function setPlayerNum(num) {
        playerNum = num;
        console.log("set player num to " + playerNum);
    }

    function setPlayerTypes(types) {
        playerTypes = types;
        for (var i = 0; i < playerTypes.length; ++i) {
            console.log("add player type: " + playerTypes[i]);
        }
    }

    ColumnLayout {
        anchors.fill: parent
    }
}
