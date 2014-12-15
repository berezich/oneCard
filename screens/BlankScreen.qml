import QtQuick 2.2

Item {
    width: defaultWidth * scaleFactor
    height: defaultHeight * scaleFactor
    //visible: false
    //opacity: (visible) ? 1.0 : 0.0
    //Behavior on opacity { NumberAnimation { duration: 400 } }
    signal backClicked()

    Keys.onBackPressed: backClicked()
    Keys.onEscapePressed: backClicked()

}
