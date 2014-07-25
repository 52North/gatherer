import QtQuick 2.0
import QtQuick.Controls 1.1
import DownloadTemplate 1.0

Rectangle {
    id:top
    width:768
    height:1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    Item {
         Connections {
             target: downloadtemplate
             onResponseReady: handlerLoader("DownloadTemplateTest.qml")
         }
     }

    Column {
        anchors.centerIn: parent
        spacing: parent.width / 10

        Button {
            id: continueButton
            width: 600
            height: 150

            text: "Download from download folder"
            onClicked: {
                downloadtemplate.download("/storage/emulated/0/Download/")
                handlerLoader("mainMenu.qml")
            }
        }
        Rectangle {
            width: 600
            height: 50
            color: "white"
            TextInput {
                id: textInputUrl
                anchors.fill:parent
                width: 80
                height: 20
                text: qsTr("")
                font.pixelSize: 25

            }}
        Button {
            id: downloadButton
            width: 600
            height: 150
            text: "Download from server"

            onClicked: {
                downloadtemplate.getSubjectList()
                //handlerLoader("DownloadTemplateTest.qml")
            }
        }
    }
    Button{
        id:buttonBack
        x: 474
        y: 891
        text: "back"
        anchors.rightMargin: 219
        anchors.bottomMargin: 116

        anchors.bottom:parent.bottom;
        anchors.right: parent.right

        onClicked: {
            handlerLoader("mainMenu.qml")
        }

    }
}
