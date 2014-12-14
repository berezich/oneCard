import QtQuick 2.0
Item
{
    id: container
    property string type: ""
    property int itemId: 0
    property alias name: itemName.text
    property alias imgSrc: img.source
    property alias imgSrcPush: imgPush.source
    //property double scaleFactor: 1
    width: 200*scaleFactor
    height: (180+50)*scaleFactor


    //VectorSprite {
    Image {
        id: img
        width: 180*scaleFactor
        height: 180*scaleFactor
        //anchors.fill: parent
        anchors.top: container.Top
        anchors.horizontalCenter: container.horizontalCenter
        source: ""
        visible: true
    }
    //VectorSprite {
    Image {
        id: imgPush
        width: 180*scaleFactor
        height: 180*scaleFactor
        //anchors.fill: parent
        anchors.horizontalCenter: container.horizontalCenter
        anchors.top: container.Top
        source: ""
        visible: false
    }


    Text{
        id: itemName
        text: "TEXT"
        anchors.horizontalCenter: container.horizontalCenter
        visible: true
        anchors.bottom: parent.bottom
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

