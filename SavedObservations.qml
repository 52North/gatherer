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
        //Component.onCompleted: visible = true
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


            //            TableViewColumn {
            //                role: "data"
            //                title: "Data"
            //                width: 250
            //            }
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
