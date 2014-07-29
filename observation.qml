import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.1
import QtPositioning 5.2

Rectangle {id:page1Container
    width: 768
    height: 1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    MessageDialog {
        id: messageDialog
        title: "Observation saved locally"
        text: "Record another observation?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            myLoader.source = "";
            myLoader.source = currentobservation.url;
        }
        onNo: {
            handlerLoader("mainMenu.qml")
        }

        //Component.onCompleted: visible = true
    }
    MessageDialog {
        id: messageDialogGPS
        title: "No GPS signal"
        text: "Turn the GPS on to include the location in the observation"

    }

    Rectangle {
        id: rect
        width: 768
        height: 600
        Loader {
            id: myLoader
            source:currentobservation.url; //file:///storage/emulated/0/Download/
        }

    }

    PositionSource {
        id: positionSource
        updateInterval: 1000
        active: false

        //        onPositionChanged: {
        //            var coord = positionSource.position.coordinate;
        //            console.log("Coordinate:", coord.longitude, coord.latitude);
        //        }
    }

    //    Text {
    //        id: textCoordinates
    //        x: 500
    //        y: 700
    //        text: qsTr(positionSource.position.coordinate.longitude + "\n" + positionSource.position.coordinate.latitude)
    //        font.pixelSize: 25
    //    }

    Text {
        id: textLat
        x: 100
        y: 700
        text: qsTr("Latitude:")
        font.pixelSize: 25
    }

    TextArea {
        id: latitude
        frameVisible: true
        textFormat: Qt.PlainText
        x: 500
        y: 700
        width: 200
        height: 40
        font.pixelSize: 25
        text: positionSource.position.coordinate.latitude
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            id: latitudeMouseArea
            parent: latitude.viewport
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: editmenu.popup()
        }
        Component.onCompleted: {

            positionSource.stop()
            if (latitude.text === "nan")
                messageDialogGPS.open()
        }
        }

                Text {
                    id: textLong
                    x: 100
                    y: 750
                    text: qsTr("Longitude:")
                    font.pixelSize: 25
                }

            TextArea {
                id: longitude
                frameVisible: true
                textFormat: Qt.PlainText
                x: 500
                y: 750
                width: 200
                height: 40
                font.pixelSize: 25
                text: positionSource.position.coordinate.longitude
                inputMethodHints: Qt.ImhDigitsOnly
                MouseArea {
                    id: longitudeMouseArea
                    parent: longitude.viewport
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                    onPressed: editmenu.popup()
                }
            }

            //   Text {
            //       id: textTimeNow
            //       x: 500
            //       y: 700
            //       text: qsTr(Qt.formatDateTime(new Date(), "dd-MM-yy\nhh:mm:ss"))
            //       font.pixelSize: 25
            //   }

            //   Text {
            //       id: textTime
            //       x: 100
            //       y: 700
            //       text: qsTr("Date/Time:")
            //       font.pixelSize: 25
            //   }

            Button{
                id:buttonCancel
                x: 450
                y: 850
                text: "cancel"

                onClicked: {
                    handlerLoader("mainMenu.qml")
                }

            }

            Connections
            {
                target: myLoader.item;
                onReturnData: {
                    currentobservation.data = data
                    currentobservation.location = "POINT(" + latitude.text + " " + longitude.text + ")"
                    currentobservation.observer = options.observer
                    currentobservation.server = options.server
                    currentobservation.time = Qt.formatDateTime(new Date(), "yyyy-MM-dd")
                    currentobservation.save();
                    messageDialog.open();
                }
            }

            Button{
                id:buttonSave
                x: 150
                y: 850
                text: "save"

                onClicked: {
                    Connections
                    {
                        target: myLoader.item.getData();
                    }
                }
            }

            Button{
                id:buttonUpdate
                x: 150
                y: 950
                text: "update location"

                onClicked: {
                    positionSource.update()
                    latitude.text = positionSource.position.coordinate.latitude
                    longitude.text = positionSource.position.coordinate.longitude
                }
            }

        }
