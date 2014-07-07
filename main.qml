import QtQuick 2.0
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
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
    }

    Column {
            anchors.centerIn: parent
            spacing: parent.width / 6

            Button {
                id: hospitalButton

                text: "Hospital"
                onClicked: console.log(hospitalButton.text + " clicked")
            }
            Button {
                id: savanneButton
                text: "Savanne"
                onClicked: console.log(savanneButton.text + " clicked")
            }
            Button {
                id: exitButton
                text: "Water-Quality"

                onClicked: Qt.quit()
            }
        }
}
