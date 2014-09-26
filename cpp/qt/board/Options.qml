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

        for (var i = 0; i < playerNum; ++i) {
            var component = Qt.createComponent("Carousel.qml");
            if (component.status === Component.Error) {
                console.error("error creating carousel: " + component.errorString());
            }

            var types = component.createObject(playersGrid,
                    {
                        values: playerTypes
                    }
            );
        }
    }

    function setPlayerTypes(types) {
        playerTypes = types;
    }

    ColumnLayout {
        id: playersGrid
        anchors.fill: parent

        spacing: 20
    }
}
