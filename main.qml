import QtQuick 2.0
import QtQuick.Controls 1.1
import DownloadTemplate 1.0


Rectangle {
    id: mainApp
    visible: true
    width: 768
    height: 1030


        signal handlerLoader(string name, int index)
        Loader {
            id:pageLoader
            source:"mainMenu.qml"
        }
        Connections {
            target:pageLoader.item
            onHandlerLoader:{pageLoader.source=name;
                if(index===2)
                    window.source="NewWindow.qml";
            }
        }

   /* menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Load")
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }*/


}
