/****************************************************************************
** Copyright (C) 2014-2014 52°North Initiative for Geospatial Open Source
** Software GmbH
**
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License version 2 as published
** by the Free Software Foundation.
**
** If the program is linked with libraries which are licensed under one of
** the following licenses, the combination of the program with the linked
** library is not considered a "derivative work" of the program:
**
**  - Apache License, version 2.0
**  - Apache Software License, version 1.0
**  - GNU Lesser General Public License, version 3
**  - Mozilla Public License, versions 1.0, 1.1 and 2.0
**  - Common Development and Distribution License (CDDL), version 1.0.
**
** Therefore the distribution of the program linked with libraries licensed
** under the aforementioned licenses, is permitted by the copyright holders
** if the distribution is compliant with both the GNU General Public
** icense version 2 and the aforementioned licenses.
**
** This program is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
** Public License for more details.
****************************************************************************/

// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This is the gui component to change the settings.

import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id:top
        width:768
        height:1030
        color: "#d4d4d4"
        signal handlerLoader(string name)

        Text{
            y: 50
            anchors.centerIn: parent
            text:"Settings"
            font.pointSize: 30
            anchors.verticalCenterOffset: -429
            anchors.horizontalCenterOffset: 0
        }


        Text {
            id: textField1
            x: 100
            y: 200
            text: qsTr("Server:")
            font.pixelSize: 25
        }
        TextArea {
            id: server
            frameVisible: true
            textFormat: Qt.PlainText
            x: 300
            y: 200
            width: 400
            height: 80
            font.pixelSize: 25
            text: options.server
            MouseArea {
                id: serverMouseArea
                parent: server.viewport
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onPressed: editmenu.popup()
            }
        }
        Text {
            id: textField2
            x: 100
            y: 400
            text: qsTr("Observer name:")
            font.pixelSize: 25
        }

        TextArea {
            id: observer
            frameVisible: true
            textFormat: Qt.PlainText
            x: 300
            y: 400
            width: 400
            height: 40
            font.pixelSize: 25
            wrapMode: TextEdit.NoWrap
            text: options.observer
            MouseArea {
                id: observerMouseArea
                parent: observer.viewport
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onPressed: editmenu.popup()
            }
        }
        Button{
            id:buttonCancel
            x: 474
            y: 891
            text: "cancel"
            anchors.rightMargin: 219
            anchors.bottomMargin: 116
            anchors.bottom:top.bottom;
            anchors.right: top.right

            onClicked: {
                handlerLoader("mainMenu.qml")
            }

        }
        Button{
            id:buttonSave
            x: 224
            y: 891
            text: "save"
            anchors.rightMargin: 469
            anchors.bottomMargin: 116
            anchors.bottom:top.bottom;
            anchors.right: top.right

            onClicked: {
                options.server = server.text
                options.observer = observer.text
                options.save()
                handlerLoader("mainMenu.qml")
            }
        }
}
