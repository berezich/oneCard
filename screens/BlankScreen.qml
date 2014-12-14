import QtQuick 2.2

Item {
    width: defaultWidth * scaleFactor
    height: defaultHeight * scaleFactor
    visible: false
    opacity: (visible) ? 1.0 : 0.0
    Behavior on opacity { NumberAnimation { duration: 400 } }
    signal backClicked()

    Keys.onBackPressed: backClicked()
    Keys.onEscapePressed: backClicked()
    //Keys.onVolumeUpPressed: appWindow.volume += 0.1
    //Keys.onVolumeDownPressed: appWindow.volune -= 0.1
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


}
