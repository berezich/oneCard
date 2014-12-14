import QtQuick 2.0

Item
{
    id: container
    property alias imgSrc: img.source
    property alias imgSrcPush: imgPush.source
    //property double scaleFactor: 1
    width: 80*scaleFactor
    height: 80*scaleFactor
    property int imgHeight: 50
    property int imgWidht: 80


    //VectorSprite {
    Image {
        id: img
        width: parent.imgWidht
        height: parent.imgHeight
        //anchors.fill: parent
        anchors.centerIn: parent
        //anchors.top: container.Top
        //anchors.horizontalCenter: container.horizontalCenter
        source: ""
        visible: true
    }
    //VectorSprite {
    Image {
        id: imgPush
        width: parent.imgWidht
        height: parent.imgHeight
        //anchors.fill: parent
        anchors.centerIn: parent
        //anchors.horizontalCenter: container.horizontalCenter
        //anchors.top: container.Top
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

