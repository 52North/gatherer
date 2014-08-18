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

// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This is the main menu with four buttons.

import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id:top
    width:768
    height:1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    Item {
         Connections {
             target: downloadtemplate
             onResponseReady: handlerLoader("DownloadTemplateFromServer.qml")
         }
     }

    Column {
        anchors.centerIn: parent
        spacing: parent.width / 10

        Button {
            id: continueButton
            width: 600
            height: 150

            text: "Continue with last template"
            onClicked: {
                if (options.current === "not")
                    continueButton.text = "Not available"
                else {
                    currentobservation.url = options.current
                    handlerLoader("Template.qml")
                }
            }
        }
        Button {
            id: selectTemplateButton
            width: 600
            height: 150
            text: "Select template"
            onClicked: handlerLoader("SelectTemplate.qml")
        }
        Button {
            id: downloadButton
            width: 600
            height: 150
            text: "Download template"

            onClicked: {
                busyIndicator.running = true
                downloadtemplate.getSubjectList(options.server)
            }
        }
        Button {
            id: observationsButton
            width:600
            height: 150
            text: "Saved observations"

            onClicked: {
                currentobservation.loadSaved();
                handlerLoader("SavedObservations.qml");
            }
        }
    }
    BusyIndicator {
        id: busyIndicator
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: 114
        running: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
