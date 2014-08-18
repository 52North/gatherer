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
// This is an example template for water point mapping

import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {id:template
    width: 768
    height: 600
    color: "#d4d4d4"
    signal returnData(string data)


    Text{
        y: 50
        anchors.centerIn: parent
        text:"Water Point Mapping"
        font.pointSize: 30
        anchors.verticalCenterOffset: -200
        anchors.horizontalCenterOffset: 0
    }


    Text {
        id: textField1
        x: 100
        y: 200
        text: qsTr("Water point name")
        font.pixelSize: 25
    }
    TextArea {
        id: field1
        frameVisible: true
        textFormat: Qt.PlainText
        x: 500
        y: 200
        width: 200
        height: 40
        font.pixelSize: 25
        MouseArea {
            id: field1MouseArea
            parent: field1.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }

    Text {
        id: textField2
        x: 100
        y: 500
        text: qsTr("Water color")
        font.pixelSize: 25
    }


    ComboBox {
        id: field2;
        width:200;
        height: 50;
        x: 500
        y: 500
        model: choices
        currentIndex: 2
        Layout.fillWidth: true
        style: ComboBoxStyle {
            label: Label {
                verticalAlignment: Qt.AlignVCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                text: control.currentText
                color: "#000000"
                anchors.fill: parent
                font.pixelSize: 25
            }
        }

    }

    ListModel {
        id: choices
        ListElement { text: "Clear" }
        ListElement { text: "Semi-dirty" }
        ListElement { text: "Dirty" }
    }


    Text {
        id: textField3
        x: 100
        y: 300
        text: qsTr("Type of maintenance needed")
        font.pixelSize: 25
    }
    TextArea {
        id: field3
        frameVisible: true
        textFormat: Qt.PlainText
        x: 500
        y: 300
        width: 200
        height: 40
        font.pixelSize: 25
        MouseArea {
            id: field3MouseArea
            parent: field3.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }

    Text {
        id: textField4
        x: 100
        y: 400
        text: qsTr("Proposed repair materials")
        font.pixelSize: 25
    }

    TextArea {
        id: field4
        frameVisible: true
        textFormat: Qt.PlainText
        x: 500
        y: 400
        width: 200
        height: 40
        font.pixelSize: 25
        wrapMode: TextEdit.NoWrap
        MouseArea {
            id: field4MouseArea
            parent: field4.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }


    function getData ()
    {
        var returnValue = "&field1=";
        returnValue = returnValue + field1.text;
        returnValue = returnValue + "&field2=";
        returnValue = returnValue + field2.currentText;
        returnValue = returnValue + "&field3=";
        returnValue = returnValue + field3.text;
        returnValue = returnValue + "&field4=";
        returnValue = returnValue + field4.text;

        template.returnData(returnValue);
    }
}
