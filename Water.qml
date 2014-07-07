import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {id:page1Container
    width: 384
    height: 640
    color:"pink"
    signal handlerLoader(string name, int index)
    Text{
        text:"First page loaded"
    }
   /*Button{
        id:buttonPage1
        text: "back"
     //Position the button in page1Container rectangle
            anchors.bottom:page1Container.bottom;
            anchors.right: page1Container.right
            MouseArea {
                    anchors.fill: parent
                    onClicked: {
                    }
            }
     }*/
}
