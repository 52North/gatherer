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
// This shows the saved observations and makes it possible to upload or delete them.

import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1
import DataObject 1.0
import CurrentObservation 1.0

Rectangle {
    id:top
    width:768
    height:1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    MessageDialog {
        id: messageDialog
        title: "Server response"
        text: currentobservation.response
        onAccepted: {
        }
    }

    Text {
        id: textField
        y: 69
        text: qsTr("Saved Observations")
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
            model: currentobservation.model
            anchors.fill: parent

            TableViewColumn {
                role: "subjectname"
                title: "Template"
                width: 350
                delegate: Component {
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        color: styleData.textColor
                        elide: styleData.elideMode
                        text: downloadtemplate.templateName(styleData.value)
                    }
                }
            }
            TableViewColumn {
                role: "time"
                title: "Date"
                width: 250
            }

        }
    }
    Button{
        id: upload
        x: 150
        y: 750
        text: "Upload"


        onClicked: {
            if (tableview.currentRow >= 0) {
                busyIndicator.running = true;
                currentobservation.upload(tableview.currentRow);
            }
        }

    }
    Button{
        id:buttonDelete
        x: 450
        y: 750
        text: "Delete"

        onClicked: {
            if (tableview.currentRow >= 0) {
                currentobservation.deleteObservation(tableview.currentRow);
                currentobservation.loadSaved();
                tableview.model = currentobservation.model;
            }
        }

    }

    Button{
        id: uploadAll
        x: 150
        y: 900
        text: "Upload All"

        onClicked: {
            busyIndicator.running = true;
            currentobservation.uploadSaved();
        }

    }
    Button{
        id:buttonCancel
        x: 450
        y: 900
        text: "Back"

        onClicked: {
            handlerLoader("mainMenu.qml")
        }

    }

    Item {
        Connections {
            target: currentobservation
            onResponseReady: {
                messageDialog.text = currentobservation.response
                messageDialog.open();
                currentobservation.loadSaved();
                tableview.model = currentobservation.model;
                busyIndicator.running = false
            }
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.verticalCenterOffset: -88
        running: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

}
