import QtQuick 2.3
import QtQuick.Window 2.2
import "components"
import "screens"

Window {
    id: page
    width: Screen.width
    height: Screen.height
    visible: true
    color: "#ededf2"
    property int defaultWidth: 720
    property int defaultHeight: 1280
    //property double scaleFactor: Math.min(Math.max(width, height) / defaultHeight, Math.min(width, height) / defaultWidth)
    property double scaleFactor: Math.min(width, height) / defaultWidth
    property var currentScreen: undefined

    function setScreen(screen) {
        console.log("width: ", Screen.width, "height: ", Screen.height)
        if (currentScreen) currentScreen.visible = false
        currentScreen = screen
        currentScreen.visible = true
        currentScreen.focus = true
    }

    Component.onCompleted: setScreen(grpScreen)

    /*
    Rectangle {
        anchors.fill: parent
        color: "black"
    }
    */
    Item {
        anchors.centerIn: parent
        width: defaultWidth * scaleFactor
        height: Screen.height
        //height: defaultHeight * scaleFactor
        clip: true
        GrpScreen {
            id: grpScreen
            onBackClicked: Qt.quit()
        }

/*
        CardsScreen {
            id: cardsScreen
            onBackClicked: setScreen(GrpScreen)
        }

        CardInfScreen {
            id: cardInfScreen
            onBackClicked: setScreen(CardsScreen)
        }
        CardAddScreen {
            id: cardAddScreen
            onBackClicked: setScreen(CardsScreen)
        }
*/

    }
}
