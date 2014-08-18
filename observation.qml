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
// This is the screen where the template is loaded in and which handles the recording of the observation

import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.1
import QtPositioning 5.2

Rectangle {id:page1Container
    width: 768
    height: 980
    color: "#d4d4d4"
    signal handlerLoader(string name)

    MessageDialog {
        id: messageDialog
        title: "Observation saved locally"
        text: "Record another observation?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            myLoader.source = "";
            myLoader.source = currentobservation.url;
        }
        onNo: {
            handlerLoader("mainMenu.qml")
        }

    }
    MessageDialog {
        id: messageDialogGPS
        title: "No GPS signal"
        text: "Turn the GPS on to include the location in the observation"

    }

    Rectangle {
        id: rect
        width: 768
        height: 600
        Loader {
            id: myLoader
            source:currentobservation.url;
        }

    }

    PositionSource {
        id: positionSource
        updateInterval: 1000
        active: true
    }


    Text {
        id: textLat
        x: 100
        y: 650
        text: qsTr("Latitude:")
        font.pixelSize: 25
    }

    TextArea {
        id: latitude
        frameVisible: true
        textFormat: Qt.PlainText
        x: 500
        y: 650
        width: 200
        height: 40
        font.pixelSize: 25
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            id: latitudeMouseArea
            parent: latitude.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
        Component.onCompleted: {

            positionSource.stop()
            if (latitude.text === "nan")
                messageDialogGPS.open()
        }
    }

    Text {
        id: textLong
        x: 100
        y: 700
        text: qsTr("Longitude:")
        font.pixelSize: 25
    }

    TextArea {
        id: longitude
        frameVisible: true
        textFormat: Qt.PlainText
        x: 500
        y: 700
        width: 200
        height: 40
        font.pixelSize: 25
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            id: longitudeMouseArea
            parent: longitude.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }

    Button{
        id:buttonCancel
        x: 450
        y: 800
        text: "cancel"

        onClicked: {
            handlerLoader("mainMenu.qml")
        }

    }

    Connections
    {
        target: myLoader.item;
        onReturnData: {
            currentobservation.data = data
            currentobservation.location = "POINT(" + latitude.text + " " + longitude.text + ")"
            currentobservation.observer = options.observer
            currentobservation.server = options.server
            currentobservation.time = Qt.formatDateTime(new Date(), "yyyy-MM-dd")
            currentobservation.save();
            messageDialog.open();
        }
    }

    Button{
        id:buttonSave
        x: 150
        y: 800
        text: "save"

        onClicked: {
            Connections
            {
                target: myLoader.item.getData();
            }
        }
    }

    Button{
        id:buttonUpdate
        x: 150
        y: 900
        text: "update location"

        onClicked: {
            latitude.text = positionSource.position.coordinate.latitude
            longitude.text = positionSource.position.coordinate.longitude
        }
    }
    Component.onCompleted: {
        latitude.text = positionSource.position.coordinate.latitude
        longitude.text = positionSource.position.coordinate.longitude
    }

}
