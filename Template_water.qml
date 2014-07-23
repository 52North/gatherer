 import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import QtPositioning 5.2

Rectangle {id:page1Container
    width: 768
    height: 1030
    color: "#d4d4d4"
    signal handlerLoader(string name, int index)

    PositionSource {
        id: positionSource
        updateInterval: 10000
        active: true

//        onPositionChanged: {
//            var coord = positionSource.position.coordinate;
//            console.log("Coordinate:", coord.longitude, coord.latitude);
//        }
    }

    Text{
        y: 50
        anchors.centerIn: parent
        text:"Water Point Mapping"
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

    TextArea {
        id: textAreaName
        frameVisible: true
        textFormat: Qt.RichText
        x: 500
        y: 200
        width: 200
        height: 40
        font.pixelSize: 25
        MouseArea {
            id: textAreaNameMouseArea
            parent: textAreaName.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }

    Text {
        id: textColor
        x: 100
        y: 200
        text: qsTr("Water point name")
        font.pixelSize: 25
    }
    TextArea {
        id: textAreaMaintenance
        frameVisible: true
        textFormat: Qt.RichText
        x: 500
        y: 300
        width: 200
        height: 40
        font.pixelSize: 25
        MouseArea {
            id: textAreaMaintenanceMouseArea
            parent: textAreaMaintenance.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }

    Text {
        id: textMaintenance
        x: 100
        y: 300
        text: qsTr("Type of maintenance needed")
        font.pixelSize: 25
    }

    TextArea {
        id: textAreaMaterials
        frameVisible: true
        textFormat: Qt.RichText
        x: 500
        y: 400
        width: 200
        height: 40
        font.pixelSize: 25
        wrapMode: TextEdit.NoWrap
        MouseArea {
            id: textAreaMaterialsMouseArea
            parent: textAreaMaterials.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
    }

    /*Rectangle {
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
*/
        Text {
            id: textMaterials
            x: 100
            y: 400
            text: qsTr("Proposed repair materials")
            font.pixelSize: 25
        }

        ComboBox {
            width:200;
            height: 50;
            x: 500
            y: 500
            id: combo
            model: choices
            currentIndex: 2
            Layout.fillWidth: true
            style: ComboBoxStyle {
                label: Label {
                    verticalAlignment: Qt.AlignVCenter
                         anchors.left: parent.left
                         anchors.leftMargin: 5
                         text: control.currentText
                         color: "#000000" //!control.enabled ? "#DADAD9" : "#6F6E6E"
                         anchors.fill: parent
                         font.pixelSize: 25
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

        Text {
            id: textCoordinates
            x: 500
            y: 600
            text: qsTr(positionSource.position.coordinate.longitude + "\n" + positionSource.position.coordinate.latitude)
            font.pixelSize: 25
        }

        Text {
            id: textCoordinate
            x: 100
            y: 600
            text: qsTr("Position:")
            font.pixelSize: 25
        }

        Text {
            id: textTimeNow
            x: 500
            y: 700
            text: qsTr(Qt.formatDateTime(new Date(), "dd-MM-yy\nhh:mm:ss"))
            font.pixelSize: 25
        }

        Text {
            id: textTime
            x: 100
            y: 700
            text: qsTr("Date/Time:")
            font.pixelSize: 25
        }

        ListModel {
            id: choices
            ListElement { text: "Clear" }
            ListElement { text: "Semi-Dirty" }
            ListElement { text: "Dirty" }
        }
    }
