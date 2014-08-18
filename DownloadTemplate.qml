/****************************************************************************
** Copyright (C) 2014-2014 52�North Initiative for Geospatial Open Source
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

//whole file is for testing, it is not used in the application.
import QtQuick 2.0
import QtQuick.Controls 1.1
import DownloadTemplate 1.0

Rectangle {
    id:top
    width:768
    height:1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    Item {
         Connections {
             target: downloadtemplate
             onResponseReady: handlerLoader("DownloadTemplateTest.qml")
         }
     }

    Column {
        anchors.centerIn: parent
        spacing: parent.width / 10

        Button {
            id: continueButton
            width: 600
            height: 150

            text: "Download from download folder"
            onClicked: {
                downloadtemplate.download("/storage/emulated/0/Download/")
                handlerLoader("mainMenu.qml")
            }
        }
        Rectangle {
            width: 600
            height: 50
            color: "white"
            TextInput {
                id: textInputUrl
                anchors.fill:parent
                width: 80
                height: 20
                text: qsTr("")
                font.pixelSize: 25

            }}
        Button {
            id: downloadButton
            width: 600
            height: 150
            text: "Download from server"

            onClicked: {
                busyIndicator.running = true
                downloadtemplate.getSubjectList(options.server)
                //currentobservation.getMap()
                //handlerLoader("DownloadTemplateTest.qml")
            }
        }
    }
    Button{
        id:buttonBack
        x: 474
        y: 891
        text: "back"
        anchors.rightMargin: 219
        anchors.bottomMargin: 116

        anchors.bottom:parent.bottom;
        anchors.right: parent.right

        onClicked: {
            handlerLoader("mainMenu.qml")
        }

    }
    BusyIndicator {
        id: busyIndicator
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: 178
        running: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
