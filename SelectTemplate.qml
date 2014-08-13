// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This shows the list of local templates and makes it possible to start one.

import QtQuick 2.0
import QtQuick.Controls 1.1
import DataObject 1.0

Rectangle {
    id:top
    width:768
    height:1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    Text {
        id: textField
        y: 69
        text: qsTr("Select Template")
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
            model: downloadtemplate.model
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
        text: "Open"

        onClicked: {
            options.current = downloadtemplate.getUrl(tableview.currentRow);
            options.save();
            currentobservation.url = downloadtemplate.getUrl(tableview.currentRow);
            handlerLoader("Template.qml")
        }

    }
    Button{
        id:buttonCancelWater
        x: 450
        y: 900
        text: "back"

        onClicked: {
            handlerLoader("mainMenu.qml")
        }

    }
}
