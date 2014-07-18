import QtQuick 2.0
import QtQuick.Controls 1.1
import DataObject 1.0

Rectangle {
    id:top
        width:768
        height:1030
        color: "#d4d4d4"
        signal handlerLoader(string name, int index)



        ListView {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 182
            width: 300; height: 500

            model: downloadtemplate.model
            delegate: Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                height: 100
                width: 400
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
                        handlerLoader(model.modelData.color,0)
                    }
                }
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
                             handlerLoader("mainMenu.qml",0)
                         }

          }
}
