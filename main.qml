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
    //property int defaultWidth: 480
    //property int defaultHeight: 640
    //visibility: Window.FullScreen
    //visible: true
    //width: 600
    //height: 800
    //property double scaleFactor: Math.min(Math.max(width, height) / defaultHeight, Math.min(width, height) / defaultWidth)
    property double scaleFactor: Math.min(width, height) / defaultWidth
    property var currentScreen: undefined

    function setScreen(screen) {
        console.log("!!!!!!!!!!!!!! width: ", Screen.width, "height: ", Screen.height)
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
        //rotation: parent.height > parent.width ? 90 : 0
        clip: true
        GrpScreen {
            id: grpScreen
            //onStartClicked: setScreen(gameScreen)
            //onAboutClicked: setScreen(aboutScreen)
            onBackClicked: Qt.quit()
        }

/*
        VectorSprite {
            anchors.fill: parent
            source: "../images/background.svg"
        }

        SplashScreen {
            id: splashScreen
            onFinished: setScreen(menuScreen)
        }
*/

/*
        GameScreen {
            id: gameScreen
            onBackClicked: setScreen(menuScreen)
        }

        AboutScreen {
            id: aboutScreen
            onBackClicked: setScreen(menuScreen)
        }
    }
*/
    }
}
