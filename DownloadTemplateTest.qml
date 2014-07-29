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

    MessageDialog {
        id: messageDialog
        title: "Template stored locally"
        text: "Download another template?"
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
        x: 150
        y: 900
        text: "Download"

        onClicked: {
            if (tableview.currentRow >= 0) {
                downloadtemplate.downloadFromUrl(options.server, downloadtemplate.getSubject(tableview.currentRow))
                messageDialog.open()
            }
        }
    }
    Button{
        id:buttonCancelWater
        x: 450
        y: 900
        text: "Back"

        onClicked: {
            handlerLoader("DownloadTemplate.qml")
        }
    }
}
