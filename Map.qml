import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtPositioning 5.2

Rectangle {id:page1Container
    width: 768
    height: 980
    color: "#d4d4d4"

    PositionSource {
        id: positionSource
        updateInterval: 1000
        active: true
        property string lat: positionSource.position.coordinate.latitude
        onPositionChanged: {
            if (positionSource.lat !== "nan") {
                point.text = "You are here\n" + positionSource.position.coordinate.latitude + " " + positionSource.position.coordinate.longitude
                point.y = (1-(positionSource.position.coordinate.latitude - image.ymin) / (image.ymax - image.ymin)) * image.height
                point.x = (positionSource.position.coordinate.longitude - image.xmin) / (image.xmax - image.xmin) * image.width
            }
            else {
                point.text = "No GPS signal"
                point.y = image.ymin
                point.x = image.xmin
            }
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Location"
        text: "You are here according to your GPS."

    }

    MessageDialog {
        id: markerDialog
        title: "Observation"
        text: "You are here"

    }

    ListModel {
        id: markers;
    }

    Flickable {
        id: flick
        width: parent.width;
        height: parent.height - 200;
        contentWidth: image.width;
        contentHeight: image.height
        clip: true
        focus: true
        boundsBehavior: Flickable.StopAtBounds;
        signal message (string messageText);
        property int amount:0;
        onMessage: {
            markerDialog.text = messageText;
            markerDialog.open();
        }

        Image {
            id: image;
            source: currentobservation.map
            property double xmin: currentobservation.xmin //6.877760913337248 // 5.65933
            property double xmax: currentobservation.xmax //6.892692511708865 // 5.68899
            property double ymin: currentobservation.ymin //52.21973335800224 // 51.96894
            property double ymax: currentobservation.ymax //52.226108841080546 // 51.98258


        }
        Image {
            id: point;
            property string text: "No GPS signal"
            y: image.ymin
            x: image.xmin
            source: "here_small.png"
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    flick.message(parent.text);
                }
            }
        }
    }
    Rectangle {
        id: zoomIn;
        x: 630;
        y: 150;
        width: 74
        height: 74
        border.color: "#000000"
        border.width: 5
        color: "#d4d4d4"

        Image {source:"Zoom-out-icon.png"; x:5;y:5}

        MouseArea{
            anchors.fill: parent
            onClicked: {
                image.height = image.height * 0.9
                image.width = image.width * 0.9
                point.y = point.y * 0.9
                point.x = point.x * 0.9
            }
        }
    }
    Rectangle {
        id: zoomOut;
        x: 630;
        y: 70;
        width: 74
        height: 74
        border.color: "#000000"
        border.width: 5
        color: "#d4d4d4"

        Image {source:"Zoom-in-icon.png"; x:5;y:5}

        MouseArea{
            anchors.fill: parent
            onClicked: {
                image.height = image.height * 1.1
                image.width = image.width * 1.1
                point.y = point.y * 1.1
                point.x = point.x * 1.1
            }
        }
    }

    Text {
        id: textFrom
        x: 50
        y: 800
        text: qsTr("From:")
        font.pixelSize: 25
    }
    TextArea {
        id: from
        frameVisible: true
        textFormat: Qt.PlainText
        x: 150
        y: 800
        width: 200
        height: 40
        font.pixelSize: 25
        text: "jjjj-mm-dd"
        inputMethodHints: Qt.ImhDate
        focus: false
        onActiveFocusChanged: {
            if (!from.activeFocus) from.closeSoftwareInputPanel();
        }
        Component.onCompleted: from.closeSoftwareInputPanel();
    }
    Text {
        id: textTo
        x: 400
        y: 800
        text: qsTr("To:")
        font.pixelSize: 25
    }
    TextArea {
        id: to
        frameVisible: true
        textFormat: Qt.PlainText
        x: 450
        y: 800
        width: 200
        height: 40
        font.pixelSize: 25
        text: "jjjj-mm-dd"
        inputMethodHints: Qt.ImhDate
        focus: false
        onActiveFocusChanged: {
            if (!to.activeFocus) to.closeSoftwareInputPanel();
        }
        Component.onCompleted: to.closeSoftwareInputPanel();
    }

    Button{
        id:buttonSave
        x: 300
        y: 900
        text: "Show observations"

        onClicked: {
            for (var i=0;i<flick.amount;i++)
                markers.get(i).code.destroy();
            markers.clear();
            flick.amount = 0;
            currentobservation.server = options.server;
            if (from.text === "jjjj-mm-dd" || from.text === "")
                currentobservation.showObservations("1970-01-01", "2100-12-31")
            else
                if (to.text === "jjjj-mm-dd" || to.text === "")
                    currentobservation.showObservations(from.text, "2100-12-31")
                else
                    currentobservation.showObservations(from.text, to.text)
        }
    }

    Button{
        id:buttonUpdate
        x: 50
        y: 900
        text: "Cancel"

        onClicked: {
            handlerLoader("mainMenu.qml")
        }
    }

    //        Button{
    //            id:buttonAdd
    //            x: 450
    //            y: 900
    //            text: "Add Point"

    //            onClicked: {
    //                try {
    //                    var object = Qt.createQmlObject("import QtQuick 2.0; Image {id: point2; property string text: 'Observation: Airport\ndate: 05-08-2014\nobserver: Bouke';
    //    y: (1-(52.22373 - image.ymin) / (image.ymax - image.ymin)) * image.height;
    //                x: (6.88340 - image.xmin) / (image.xmax - image.xmin) * image.width; signal rem();
    //                source: 'marker_small.png'; MouseArea {anchors.fill: parent; onClicked: {flick.message(parent.text)}}}"// onRem:{parent.source='';console.log('removed')}
    ////Component.onCompleted: flick.remo.connect(rem)}"
    //                                                    , image.parent);
    //                    markers.append({"code":object});
    //                    flick.amount += 1;
    //                } catch(err) {
    //                    dialog.show('Error on line ' + err.qmlErrors[0].lineNumber + '\n' + err.qmlErrors[0].message);
    //                }
    //            }
    //        }

    Item {
        Connections {
            target: currentobservation
            onAddPoint: {
                try {
                    flick.amount += 1;
                    var object = Qt.createQmlObject("import QtQuick 2.0; Image {id: observationMarker;
                    property string text: 'Observation: " + observation + "\nDate: " + time + "\nObserver: " + observer + "';
                    y: (1-(" + lat + " - image.ymin) / (image.ymax - image.ymin)) * image.height - 51;
                    x: (" + lon + " - image.xmin) / (image.xmax - image.xmin) * image.width - 20;
                    source: 'marker_small.png'; MouseArea {anchors.fill: parent; onClicked: {flick.message(parent.text)}}}",image.parent);
                    markers.append({"code":object});
                } catch(err) {
                    console.log('Error on line ' + err.qmlErrors[0].lineNumber + '\n' + err.qmlErrors[0].message);
                }
            }

        }
    }

}

