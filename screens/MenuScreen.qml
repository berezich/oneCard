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
import "../components"

BlankScreen {
    id: menuScreen
    signal startClicked()
    signal aboutClicked()

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 40 * scaleFactor
        anchors.bottomMargin: 20 * scaleFactor

        CuteHeader {
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "Cute Plane"
        }

        CuteButton {
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            text: "Start"
            onClicked: menuScreen.startClicked()
        }

        CuteButton {
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            text: "About"
            onClicked: menuScreen.aboutClicked()
        }

        CuteLabel {
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            text: "Highscore: " + highscore
        }
    }
}
