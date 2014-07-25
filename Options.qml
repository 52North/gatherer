import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id:top
        width:768
        height:1030
        color: "#d4d4d4"
        signal handlerLoader(string name)

        Text{
            y: 50
            anchors.centerIn: parent
            text:"Settings"
            font.pointSize: 30
            anchors.verticalCenterOffset: -429
            anchors.horizontalCenterOffset: 0
        }


        Text {
            id: textField1
            x: 100
            y: 200
            text: qsTr("Server:")
            font.pixelSize: 25
        }
        TextArea {
            id: server
            frameVisible: true
            textFormat: Qt.PlainText
            x: 300
            y: 200
            width: 400
            height: 40
            font.pixelSize: 25
            text: options.server
            MouseArea {
                id: serverMouseArea
                parent: server.viewport
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onPressed: editmenu.popup()
            }
        }
        Text {
            id: textField2
            x: 100
            y: 300
            text: qsTr("Observer name:")
            font.pixelSize: 25
        }

        TextArea {
            id: observer
            frameVisible: true
            textFormat: Qt.PlainText
            x: 300
            y: 300
            width: 400
            height: 40
            font.pixelSize: 25
            wrapMode: TextEdit.NoWrap
            text: options.observer
            MouseArea {
                id: observerMouseArea
                parent: observer.viewport
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onPressed: editmenu.popup()
            }
        }
        Button{
            id:buttonCancel
            x: 474
            y: 891
            text: "cancel"
            anchors.rightMargin: 219
            anchors.bottomMargin: 116
            //Position the button in page1Container rectangle
            anchors.bottom:top.bottom;
            anchors.right: top.right

            onClicked: {
                handlerLoader("mainMenu.qml")
            }

        }
        Button{
            id:buttonSave
            x: 224
            y: 891
            text: "save"
            anchors.rightMargin: 469
            anchors.bottomMargin: 116
            //Position the button in page1Container rectangle
            anchors.bottom:top.bottom;
            anchors.right: top.right

            onClicked: {
                options.server = server.text
                options.observer = observer.text
                options.save()
                handlerLoader("mainMenu.qml")
            }
        }
}
