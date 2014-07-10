import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {id:page1Container
    width: 768
    height: 1030
    color: "#d4d4d4"
    signal handlerLoader(string name, int index)


    Text{
        y: 50
        anchors.centerIn: parent
        text:"Animal observation"
        font.pointSize: 30
        anchors.verticalCenterOffset: -457
        anchors.horizontalCenterOffset: 0
    }

   Button{
        id:buttonCancelWater
        x: 474
        y: 891
        text: "cancel"
        anchors.rightMargin: 219
        anchors.bottomMargin: 116
     //Position the button in page1Container rectangle
            anchors.bottom:page1Container.bottom;
            anchors.right: page1Container.right

                    onClicked: {
                        handlerLoader("mainMenu.qml",0)
                    }

     }

   Button{
        id:buttonSaveWater
        x: 224
        y: 891
        text: "save"
        anchors.rightMargin: 469
        anchors.bottomMargin: 116
     //Position the button in page1Container rectangle
            anchors.bottom:page1Container.bottom;
            anchors.right: page1Container.right

                    onClicked: {
                        handlerLoader("mainMenu.qml",0)
                    }

     }

   Rectangle {
       x: 386
       y: 192
       width: 150
       height: 30
       color: "white"
     TextInput {
         id: textInputColor
        anchors.fill:parent
         text: qsTr("")
         inputMask: qsTr("")
         font.pixelSize: 25
     }
   }

     Text {
         id: textColor
         x: 108
         y: 192
         text: qsTr("Kind of animal")
         font.pixelSize: 25
    }
     Rectangle {
         x: 386
         y: 301
         width: 150
         height: 30
         color: "white"
     TextInput {
         id: textInputMaintenance
         anchors.fill:parent
        width: 80
         height: 20
         text: qsTr("")
         font.pixelSize: 25

     }}

     Text {
         id: textMaintenance
         x: 108
         y: 301
         text: qsTr("Amount")
         font.pixelSize: 25
     }


}
