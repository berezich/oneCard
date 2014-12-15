import QtQuick 2.0
Item
{
    id: container
    property string type: ""
    property int itemId: 0
    property alias name: itemName.text
    property string imgSrc: img.source
    property string imgSrcPush: imgPush.source
    property int imgH: 180
    property int imgW: 180
    width: (imgW+20)*scaleFactor
    height: (imgH+50)*scaleFactor
    clip: false


    Image {
        id: img
        width: imgW*scaleFactor
        height: imgH*scaleFactor
        anchors.top: container.Top
        anchors.horizontalCenter: container.horizontalCenter
        source: imgSrc
        visible: true
    }

    Image {
        id: imgPush
        width: imgW*scaleFactor
        height: imgH*scaleFactor
        anchors.horizontalCenter: container.horizontalCenter
        anchors.top: container.Top
        source: imgSrcPush
        visible: false
    }


    Text{
        id: itemName
        text: ""
        anchors.horizontalCenter: container.horizontalCenter
        visible: true
        anchors.top: img.bottom

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

