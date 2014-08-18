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
// This is the gui component to download a template from a server.

import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1
import DataObject 1.0

Rectangle {
    id:top
    width:768
    height:1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    // to receive signals from downloadtemplate object
    Item {
         Connections {
             target: downloadtemplate
             onDownloadMap: messageDialog.open()
             onDownloadObservationsSig: messageDialogObservations.open()
             onResponseReady: {
                 busyIndicator.running = false;
                 messageDialogReady.open()
             }
         }
     }

    BusyIndicator {
        id: busyIndicator
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: 268
        running: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    MessageDialog {
        id: messageDialog
        title: "Basemap"
        text: "There is a basemap available. Download basemap?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            busyIndicator.running = true;
            downloadtemplate.getMap()
            }
        onNo: {
            messageDialogObservations.open()
        }
    }

    MessageDialog {
        id: messageDialogObservations
        title: "Historic observations"
        text: "Do you want to download historical observations?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            busyIndicator.running = true;
            downloadtemplate.downloadObservations(options.server)
            }
        onNo: {
            messageDialogReady.open()
        }
    }

    MessageDialog {
        id: messageDialogReady
        title: "Template saved"
        text: "The template is now ready for use. Download another?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            }
        onNo: {
            handlerLoader("mainMenu.qml")
        }
    }

    Text {
        id: textField
        y: 69
        text: qsTr("Download Template")
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 25
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 182
        width: 600;
        height: 500
        TableView{
            id: tableview
            model: downloadtemplate.subjectsModel
            anchors.fill: parent

            TableViewColumn {
                role: "name"
                title: "Template"
                width: 600

                resizable: false
                movable: false
            }
            TableViewColumn {
                role: "url"
                title: "url"
                width: 0
                resizable: false
                movable: false
                visible: false
            }

        }
    }

    Button{
        id: open
        x: 150
        y: 900
        text: "Download"

        onClicked: {
            if (tableview.currentRow >= 0 && busyIndicator.running === false) {
                downloadtemplate.downloadFromUrl(options.server, downloadtemplate.getSubject(tableview.currentRow))
            }
        }
    }
    Button{
        id:buttonCancelWater
        x: 450
        y: 900
        text: "Back"

        onClicked: {
            if (busyIndicator.running === false)
            handlerLoader("mainMenu.qml")
        }
    }
}
