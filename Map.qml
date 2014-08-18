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
// This shows the map of the template and makes it possible to show historic observations

import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtPositioning 5.2

Rectangle {id:page1Container
    width: 768
    height: 980
    color: "#d4d4d4"

    PositionSource {
        id: positionSource
        updateInterval: 1000
        active: true
        property string lat: positionSource.position.coordinate.latitude
        onPositionChanged: {
            if (positionSource.lat !== "nan") {
                point.text = "You are here\n" + positionSource.position.coordinate.latitude + " " + positionSource.position.coordinate.longitude
                point.y = (1-(positionSource.position.coordinate.latitude - image.ymin) / (image.ymax - image.ymin)) * image.height - 15
                point.x = (positionSource.position.coordinate.longitude - image.xmin) / (image.xmax - image.xmin) * image.width - 15
            }
            else {
                point.text = "No GPS signal"
                point.y = image.ymin
                point.x = image.xmin
            }
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Location"
        text: "You are here according to your GPS."

    }

    MessageDialog {
        id: markerDialog
        title: "Observation"
        text: "You are here"

    }

    ListModel {
        id: markers;
    }

    Flickable {
        id: flick
        width: parent.width;
        height: parent.height - 200;
        contentWidth: image.width;
        contentHeight: image.height
        clip: true
        focus: true
        boundsBehavior: Flickable.StopAtBounds;
        signal message (string messageText);
        property int amount:0;
        onMessage: {
            markerDialog.text = messageText;
            markerDialog.open();
        }

        Image {
            id: image;
            source: currentobservation.map
            property double xmin: currentobservation.xmin //6.877760913337248 // 5.65933
            property double xmax: currentobservation.xmax //6.892692511708865 // 5.68899
            property double ymin: currentobservation.ymin //52.21973335800224 // 51.96894
            property double ymax: currentobservation.ymax //52.226108841080546 // 51.98258


        }
        Image {
            id: point;
            property string text: "No GPS signal"
            y: image.ymin
            x: image.xmin
            source: "hereblue_small.png"
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    flick.message(parent.text);
                }
            }
        }
    }

    Rectangle {
        id: zoomOut;
        x: 630;
        y: 150;
        width: 74
        height: 74
        border.color: "#000000"
        border.width: 5
        color: "#d4d4d4"

        Image {source:"Zoom-out-icon.png"; x:5;y:5}

        MouseArea{
            anchors.fill: parent
            onClicked: {
                image.height = image.height * (1 / 1.1)
                image.width = image.width * (1 / 1.1)
                point.y = point.y * (1 / 1.1)
                point.x = point.x * (1 / 1.1)
                // To make it zoom to the center of the view
                flick.contentX -= (1 - 1 / 1.1) * (0.5 * flick.width + flick.contentX);
                flick.contentY -= (1 - 1 / 1.1) * (0.5 * flick.height + flick.contentY);
            }
        }
    }
    Rectangle {
        id: zoomIn;
        x: 630;
        y: 70;
        width: 74
        height: 74
        border.color: "#000000"
        border.width: 5
        color: "#d4d4d4"

        Image {source:"Zoom-in-icon.png"; x:5;y:5}

        MouseArea{
            anchors.fill: parent
            onClicked: {
                image.height = image.height * 1.1
                image.width = image.width * 1.1
                point.y = point.y * 1.1
                point.x = point.x * 1.1
                // To make it zoom to the center of the view
                flick.contentX += 0.1 * (0.5 * flick.width + flick.contentX);
                flick.contentY += 0.1 * (0.5 * flick.height + flick.contentY);
            }
        }
    }

    Text {
        id: textFrom
        x: 50
        y: 800
        text: qsTr("From:")
        font.pixelSize: 25
    }
    TextArea {
        id: from
        frameVisible: true
        textFormat: Qt.PlainText
        x: 150
        y: 800
        width: 200
        height: 40
        font.pixelSize: 25
        text: "jjjj-mm-dd"
        inputMethodHints: Qt.ImhDate
        focus: false
    }
    Text {
        id: textTo
        x: 400
        y: 800
        text: qsTr("To:")
        font.pixelSize: 25
    }
    TextArea {
        id: to
        frameVisible: true
        textFormat: Qt.PlainText
        x: 450
        y: 800
        width: 200
        height: 40
        font.pixelSize: 25
        text: "jjjj-mm-dd"
        inputMethodHints: Qt.ImhDate
        focus: false
    }

    Button{
        id:buttonSave
        x: 300
        y: 900
        text: "Show observations"

        onClicked: {
            for (var i=0;i<flick.amount;i++)
                markers.get(i).code.destroy();
            markers.clear();
            flick.amount = 0;
            currentobservation.server = options.server;
            if (from.text === "jjjj-mm-dd" || from.text === "")
                currentobservation.showObservations("1970-01-01", "2100-12-31")
            else
                if (to.text === "jjjj-mm-dd" || to.text === "")
                    currentobservation.showObservations(from.text, "2100-12-31")
                else
                    currentobservation.showObservations(from.text, to.text)
        }
    }

    Button{
        id:buttonUpdate
        x: 50
        y: 900
        text: "Cancel"

        onClicked: {
            handlerLoader("mainMenu.qml")
        }
    }

    Item {
        Connections {
            target: currentobservation
            onAddPoint: {
                try {
                    flick.amount += 1;
                    if (newObservation)
                        var object = Qt.createQmlObject("import QtQuick 2.0; Image {id: observationMarker;
                        property string text: 'Observation: " + observation + "\nDate: " + time + "\nObserver: " + observer + "';
                        y: (1-(" + lat + " - image.ymin) / (image.ymax - image.ymin)) * image.height - 51;
                        x: (" + lon + " - image.xmin) / (image.xmax - image.xmin) * image.width - 20;
                        source: 'markerblue_small.png'; MouseArea {anchors.fill: parent; onClicked: {flick.message(parent.text)}}}",image.parent);
                    else
                        var object = Qt.createQmlObject("import QtQuick 2.0; Image {id: observationMarker;
                        property string text: 'Observation: " + observation + "\nDate: " + time + "\nObserver: " + observer + "';
                        y: (1-(" + lat + " - image.ymin) / (image.ymax - image.ymin)) * image.height - 51;
                        x: (" + lon + " - image.xmin) / (image.xmax - image.xmin) * image.width - 20;
                        source: 'markergreen_small.png'; MouseArea {anchors.fill: parent; onClicked: {flick.message(parent.text)}}}",image.parent);
                    markers.append({"code":object});
                } catch(err) {
                    console.log('Error on line ' + err.qmlErrors[0].lineNumber + '\n' + err.qmlErrors[0].message);
                }
            }

        }
    }

}

