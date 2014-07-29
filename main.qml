import QtQuick 2.2
import QtQuick.Controls 1.1
import "content"



ApplicationWindow {
    id: mainApp
    visible: true
    width: 768
    height: 1030

//    toolBar: BorderImage {
//        border.bottom: 8
//        source: "toolbar.png"
//        width: parent.width
//        height: 100

//        Rectangle {
//            id: backButton
//            width: opacity ? 60 : 0
//            anchors.left: parent.left
//            anchors.leftMargin: 20
//            opacity: stackView.depth > 1 ? 1 : 0
//            anchors.verticalCenter: parent.verticalCenter
//            antialiasing: true
//            height: 60
//            radius: 4
//            color: backmouse.pressed ? "#222" : "transparent"
//            Behavior on opacity { NumberAnimation{} }
//            Image {
//                anchors.verticalCenter: parent.verticalCenter
//                source: "navigation_previous_item.png"
//            }
//            MouseArea {
//                id: backmouse
//                anchors.fill: parent
//                anchors.margins: -10
//                onClicked: stackView.pop()
//            }
//        }

//        Text {
//            font.pixelSize: 42
//            Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
//            x: backButton.x + backButton.width + 20
//            anchors.verticalCenter: parent.verticalCenter
//            color: "white"
//            text: "Gatherer"
//        }
//    }


        signal handlerLoader(string name)
        Loader {
            id:pageLoader
            source:"mainMenu.qml"
        }
        Connections {
            target:pageLoader.item
            onHandlerLoader:{pageLoader.source=name;
            }
        }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Home")
                onTriggered: pageLoader.source="mainMenu.qml"
            }
            MenuItem {
                text: qsTr("Settings")
                onTriggered: pageLoader.source="Options.qml"
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
//        StackView {
//            id: stackView
//            anchors.fill: parent
//            // Implements back key navigation
//            focus: true
//            Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
//                                 stackView.pop();
//                                 event.accepted = true;
//                             }


//        }


}
