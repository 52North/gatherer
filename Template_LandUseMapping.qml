import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {id:template
    width: 768
    height: 600
    color: "#d4d4d4"
    signal returnData(string data)


    Text{
        y: 50
        anchors.centerIn: parent
        text:"Landuse Mapping"
        font.pointSize: 30
        anchors.verticalCenterOffset: -200
        anchors.horizontalCenterOffset: 0
    }

    Text {
        id: textField1
        x: 100
        y: 200
        text: qsTr("Land cover class")
        font.pixelSize: 25
    }


    ComboBox {
        id: field1;
        width:600;
        height: 50;
        x: 100
        y: 200
        model: choices
        currentIndex: 23
        Layout.fillWidth: true
        style: ComboBoxStyle {
            label: Label {
                verticalAlignment: Qt.AlignVCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                text: control.currentText
                color: "#000000"
                anchors.fill: parent
                font.pixelSize: 20
            }
        }

    }

    ListModel {
        id: choices
        ListElement { text: "Continuous Urban fabric" }
        ListElement { text: "Discontinuous Dense Urban Fabric" }
        ListElement { text: "Discontinuous Medium Density" }
        ListElement { text: "Urban Fabric" }
        ListElement { text: "Discontinuous Low Density Urban Fabric" }
        ListElement { text: "Discontinuous Very Low Density Urban Fabric" }
        ListElement { text: "Isolated Structures" }
        ListElement { text: "Industrial, commercial, public, military and private units" }
        ListElement { text: "Fast transit roads and associated land" }
        ListElement { text: "Other roads and associated land" }
        ListElement { text: "Railways and associated land" }
        ListElement { text: "Port areas" }
        ListElement { text: "Airports" }
        ListElement { text: "Mineral extraction and dump sites" }
        ListElement { text: "Construction sites" }
        ListElement { text: "Land without current use" }
        ListElement { text: "Green urban areas" }
        ListElement { text: "Sports and leisure facilities" }
        ListElement { text: "Agricultural Areas, semi-natural areas and wetlands" }
        ListElement { text: "Forests" }
        ListElement { text: "Water" }
        ListElement { text: "No data" }

    }

    function getData ()
    {
        var returnValue = "&field1=";
        returnValue = returnValue + field1.currentText;

        template.returnData(returnValue);
    }

}
