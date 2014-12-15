import QtQuick 2.0

Item
{
    id: container
    property alias imgSrc: img.source
    property alias imgSrcPush: imgPush.source
    width: 80*scaleFactor
    height: 80*scaleFactor
    property int imgHeight: 50
    property int imgWidht: 80


    Image {
        id: img
        width: parent.imgWidht*scaleFactor
        height: parent.imgHeight*scaleFactor
        anchors.centerIn: parent
        //anchors.top: container.Top
        //anchors.horizontalCenter: container.horizontalCenter
        source: ""
        visible: true
    }
    Image {
        id: imgPush
        width: parent.imgWidht*scaleFactor
        height: parent.imgHeight*scaleFactor
        anchors.centerIn: parent
        source: ""
        visible: false
    }


    MouseArea {
        anchors.fill: parent
        onPressed: {
            imgPush.visible = true;
            img.visible = false;
        }
        onReleased: {
            imgPush.visible = false;
            img.visible = true;
        }
        onExited: {
            imgPush.visible = false;
            img.visible = true;
        }

    }
}

