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
        text:"Water access points"
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
         text: qsTr("Water color")
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
         text: qsTr("Type of maintenance")
         font.pixelSize: 25
     }

    /* FocusScope {
         id: focusScope;
         width: 400;
         height: textInput.paintedHeight + (2 * textInput.anchors.topMargin);
         x: 100
         y: 700

         property alias  value                          : textInput.text;
         property alias  fontSize                       : textInput.font.pointSize;
         property alias  textColor                      : textInput.color;
         property alias  placeHolder                    : typeSomething.text;

         Rectangle {
             id: background;
             anchors.fill: parent;
             color: "#AAAAAA";
             radius: 5;
             antialiasing: true;
             border {
                 width: 3;
                 color: (focusScope.activeFocus ? "red" : "steelblue");
             }
         }
         TextEdit {
             id: textInput;
             focus: true
             selectByMouse: true
             font.pointSize: 20;
             wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere;
             color: "black";
             anchors {
                 top: parent.top;
                 topMargin: 10;
                 left: parent.left;
                 leftMargin: 10;
                 right: parent.right;
                 rightMargin: 10;
             }
         }
         Text {
             id: typeSomething;
             text: "Type something...";
             color: "gray";
             opacity: (value === "" ? 1.0 : 0.0);
             font {
                 italic: true
                 pointSize: fontSize;
             }
             anchors {
                 left: parent.left;
                 right: parent.right;
                 leftMargin: 10;
                 rightMargin: 10;
                 verticalCenter: parent.verticalCenter;
             }

             Behavior on opacity { NumberAnimation { duration: 250; } }
         }
         MouseArea {
             visible: (!focusScope.activeFocus);
             anchors.fill: parent
             onClicked: { textInput.forceActiveFocus(); }
         }
         Text {
             id: clear;
             text: "\u2717" // 'x' //"\u2713"
             color: 'steelblue';
             font.pixelSize: 30;
             opacity: (value !== "" ? 1.0 : 0.0);
             anchors {
                 right: parent.right;
                 bottom: parent.bottom;
                 margins: 5;
             }

             Behavior on opacity { NumberAnimation { duration: 250; } }

             MouseArea {
                 anchors.fill: parent
                 onClicked: {
                     value = "";
                     focusScope.focus = false;
                 }
             }
         }
     }*/
}
