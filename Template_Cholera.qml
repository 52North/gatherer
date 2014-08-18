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
// This is an example template for health mapping - cholera

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
        text:"Health mapping - Cholera"
        font.pointSize: 30
        anchors.verticalCenterOffset: -200
        anchors.horizontalCenterOffset: 0
    }


    Text {
        id: textField1
        x: 100
        y: 200
        text: qsTr("Disease Occurrence Id")
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
        inputMethodHints: Qt.ImhDigitsOnly
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
        y: 300
        text: qsTr("Patient name")
        font.pixelSize: 25
    }

    TextArea {
        id: field2
        frameVisible: true
        textFormat: Qt.PlainText
        x: 500
        y: 300
        width: 200
        height: 40
        font.pixelSize: 25
        wrapMode: TextEdit.NoWrap
        MouseArea {
            id: field2MouseArea
            parent: field2.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }


    GroupBox {
        id: field3
        width: 600
        height: 200
        x: 100
        y: 350
        title: "Symptoms"

            Row {
                anchors.verticalCenterOffset: -30
                anchors.centerIn: parent
                spacing: 10
                CheckBox {
                    id: diarrhea
                    text: "Diarrhea"
                    checked: false
                    Layout.minimumWidth: 100
                    style: CheckBoxStyle {
                        label: Text {
                            text: control.text
                            color: "#000000"
                            renderType: Text.NativeRendering
                            font.pixelSize: 25
                        }
                    }
                }
                CheckBox {
                    id: dehydration
                    text: "Dehydration"
                    checked: false
                    Layout.minimumWidth: 100
                    style: CheckBoxStyle {
                        label: Text {
                            text: control.text
                            color: "#000000"
                            renderType: Text.NativeRendering
                            font.pixelSize: 25
                        }
                    }
                }
            }
            Row {
                anchors.verticalCenterOffset: 30
                anchors.centerIn: parent
                spacing: 10
                CheckBox {
                    id: vomiting
                    text: "Vomiting"
                    checked: false
                    Layout.minimumWidth: 100
                    style: CheckBoxStyle {
                        label: Text {
                            text: control.text
                            color: "#000000"
                            renderType: Text.NativeRendering
                            font.pixelSize: 25
                        }
                    }
                }
                CheckBox {
                    id: abdominalPain
                    text: "AbdominalPain"
                    checked: false
                    Layout.minimumWidth: 100
                    style: CheckBoxStyle {
                        label: Text {
                            text: control.text
                            color: "#000000"
                            renderType: Text.NativeRendering
                            font.pixelSize: 25
                        }
                    }
                }
            }
}

    function getData ()
    {
        var returnValue = "&field1=";
        returnValue = returnValue + field1.text;
        returnValue = returnValue + "&field2=";
        returnValue = returnValue + field2.text;
        returnValue = returnValue + "&field3=";
        if (diarrhea.checked)
            returnValue = returnValue + "Diarrhea;";
        if (dehydration.checked)
            returnValue = returnValue + "Dehydration;";
        if (vomiting.checked)
            returnValue = returnValue + "Vomiting;";
        if (abdominalPain.checked)
            returnValue = returnValue + "AbdominalPain";
        template.returnData(returnValue);
    }
}
