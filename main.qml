// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This is the main gui file, it handles the changes of the screens and provides the top menu

import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    id: mainApp
    visible: true
    width: 768
    height: 1030

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
}
