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
        text:"WaterM Point Mapping"
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
        x: 500
        y: 200
        width: 200
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
        x: 100
        y: 200
        text: qsTr("Water point name")
        font.pixelSize: 25
    }
    Rectangle {
        x: 500
        y: 300
        width: 200
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
        x: 100
        y: 300
        text: qsTr("Type of maintenance needed")
        font.pixelSize: 25
    }

        Rectangle {
            x: 500
            y: 400
            width: 200
            height: 30
            color: "white"
            TextInput {
                id: textInputMaterials
                anchors.fill:parent
                width: 80
                height: 20
                text: qsTr("")
                font.pixelSize: 25

            }}

        Text {
            id: textMaterials
            x: 100
            y: 400
            text: qsTr("Proposed repair materials")
            font.pixelSize: 25
        }

        Rectangle {
            width:200;
            height: 50;
            x: 500
            y: 500

            Rectangle {
                    id:comboBox
                    property variant items: ["Clear", "Semi-dirty", "Dirty"]
                    property alias selectedItem: chosenItemText.text;
                    property alias selectedIndex: listView.currentIndex;
                    signal comboClicked;
                    width: 200;
                    height: 50;
                    z: 150;
                    smooth:true;

                    Rectangle {
                        id:chosenItem
                        radius:4;
                        width:parent.width;
                        height:comboBox.height;
                        color: "lightsteelblue"
                        smooth:true;
                        Text {
                            anchors.top: parent.top;
                            anchors.left: parent.left;
                            anchors.margins: 8;
                            id:chosenItemText
                            text:comboBox.items[0];
                            font.family: "Arial"
                            font.pointSize: 12;
                            smooth:true
                        }

                        MouseArea {
                            anchors.fill: parent;
                            onClicked: {
                                comboBox.state = comboBox.state==="dropDown"?"":"dropDown"
                            }
                        }
                    }

                    Rectangle {
                        id:dropDown
                        width:comboBox.width;
                        height:0;
                        clip:true;
                        radius:4;
                        anchors.top: chosenItem.bottom;
                        anchors.margins: 2;
                        color: "lightgray"

                        ListView {
                            id:listView
                            height:1000;
                            model: comboBox.items
                            currentIndex: 0
                            delegate: Item{
                                width:comboBox.width;
                                height: comboBox.height;

                                Text {
                                    text: modelData
                                    anchors.top: parent.top;
                                    anchors.left: parent.left;
                                    anchors.margins: 5;
                                    font.family: "Arial"
                                    font.pointSize: 12;

                                }
                                MouseArea {
                                    anchors.fill: parent;
                                    onClicked: {
                                        comboBox.state = ""
                                        var prevSelection = chosenItemText.text
                                        chosenItemText.text = modelData
                                        if(chosenItemText.text != prevSelection){
                                            comboBox.comboClicked();
                                        }
                                        listView.currentIndex = index;
                                    }
                                }
                            }
                        }
                    }

                    Component {
                        id: highlight
                        Rectangle {
                            width:comboBox.width;
                            height:comboBox.height;
                            color: "red";
                            radius: 4
                        }
                    }

                    states: State {
                        name: "dropDown";
                        PropertyChanges { target: dropDown; height:50*comboBox.items.length }
                    }

                    transitions: Transition {
                        NumberAnimation { target: dropDown; properties: "height"; easing.type: Easing.OutExpo; duration: 1000 }
                    }
                }
            }


        Text {
            id: textWaterColor
            x: 100
            y: 500
            text: qsTr("Water color")
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
