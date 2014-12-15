/****************************************************************************
**
** Copyright (C) 2014 Oleg Yadrov.
** Contact: wearyinside@gmail.com
**
** This file is part of Cute Plane.
**
** Cute Plane is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Cute Plane is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Cute Plane. If not, see http://www.gnu.org/licenses/.
**
****************************************************************************/

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import "../components"

BlankScreen {
    id: grpScreen
    //signal itemClicked(int id)

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 70*scaleFactor

        Rectangle{
            id: cap
            width: grpScreen.width
            height: 120*scaleFactor
            anchors.top: grpScreen.top
            color: "#80bab7"
            Text{
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 50*scaleFactor
                text: "ВАШИ КАРТЫ"
                font.bold: false
                color: "white"
            }

            CapIcon{
                anchors.right: cap.right; anchors.rightMargin: 30*scaleFactor
                anchors.verticalCenter: cap.verticalCenter
                width: 80*scaleFactor
                height: 80*scaleFactor
                visible: true
                imgSrc: "../svg/oblako.svg"
                imgSrcPush: "../svg/oblakoPUSH.svg"
                imgHeight: 50*scaleFactor
                imgWidht: 80*scaleFactor
            }
        }
        Grid {
                id: groups
                Layout.alignment: Qt.AlignHCenter
                clip: true
                rows: 6; columns: 3; spacing: 30*scaleFactor

                Icon { name: "Транспорт"; itemId: 1; imgSrc: "../svg/car.svg"; imgSrcPush: "../svg/carPUSH.svg"}
                Icon { name: "Спорт"; itemId: 2; imgSrc: "../svg/fit.svg"; imgSrcPush: "../svg/fitPUSH.svg"}
                Icon { name: "Рестораны"; itemId: 3; imgSrc: "../svg/food.svg"; imgSrcPush: "../svg/foodPUSH.svg"}
                Icon { name: "Аптеки"; itemId: 4; imgSrc: "../svg/med.svg"; imgSrcPush: "../svg/medPUSH.svg"}
                Icon { name: "Туризм"; itemId: 5; imgSrc: "../svg/plane.svg"; imgSrcPush: "../svg/planePUSH.svg"}
                Icon { name: "Ремонт"; itemId: 6; imgSrc: "../svg/rebild.svg"; imgSrcPush: "../svg/rebildPUSH.svg"}
                Icon { name: "Магазины"; itemId: 7; imgSrc: "../svg/shop.svg"; imgSrcPush: "../svg/shopPUSH.svg"}
                Icon { name: "Солярий"; itemId: 2; imgSrc: "../svg/sun.svg"; imgSrcPush: "../svg/sunPUSH.svg"}
                Icon { name: "Разное"; itemId: 8; imgSrc: "../svg/different.svg"; imgSrcPush: "../svg/differentPUSH.svg"}
                Icon { name: ""; itemId: -1; imgSrc: "../svg/new.svg"; imgSrcPush: "../svg/newPUSH.svg"}

            }

    }

}
