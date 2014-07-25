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
        x: 256
        y: 69
        text: qsTr("Select Template")
        font.pointSize: 25
    }

    ListView {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 182
        width: 300; height: 500

        model: downloadtemplate.model
        delegate: Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            height: 100
            width: 600
            border.width: 1
            border.color: "black"
            //color: model.modelData.color
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: name }
            MouseArea {
                id: mousearea2
                anchors.fill: parent
                onClicked: {
                    textField.text = qsTr("Loading template...")
                    currentobservation.url = model.modelData.color;
                    //currentobservation.name = model.modelData.name;
                    handlerLoader("Observation.qml")
                }
            }
        }
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
                role: "color"
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
        x: 193
        y: 891
        text: "Open"
        anchors.rightMargin: 500
        anchors.bottomMargin: 116
        //Position the button in page1Container rectangle
        anchors.bottom:top.bottom;
        anchors.right: top.right

        onClicked: {
            console.log(tableview.currentRow)
            console.log(tableview.childAt(tableview.currentRow,1).color)
            currentobservation.url = tableview.childAt(tableview.currentRow,1);
            handlerLoader("Observation.qml")
        }

    }
    Button{
        id:buttonCancelWater
        x: 474
        y: 891
        text: "back"
        anchors.rightMargin: 219
        anchors.bottomMargin: 116
        //Position the button in page1Container rectangle
        anchors.bottom:top.bottom;
        anchors.right: top.right

        onClicked: {
            handlerLoader("mainMenu.qml")
        }

    }
}
