import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import QtPositioning 5.2

Rectangle {id:page1Container
   width: 768
   height: 1030
   color: "#d4d4d4"
   signal handlerLoader(string name)

   Rectangle {
   width: 768
   height: 600
     Loader {
         id: myLoader
       source:currentobservation.url; //file:///storage/emulated/0/Download/
     }

   }

   PositionSource {
       id: positionSource
       updateInterval: 10000
       active: true

//        onPositionChanged: {
//            var coord = positionSource.position.coordinate;
//            console.log("Coordinate:", coord.longitude, coord.latitude);
//        }
   }

   Text {
       id: textCoordinates
       x: 500
       y: 700
       text: qsTr(positionSource.position.coordinate.longitude + "\n" + positionSource.position.coordinate.latitude)
       font.pixelSize: 25
   }

   Text {
       id: textCoordinate
       x: 100
       y: 700
       text: qsTr("Position:")
       font.pixelSize: 25
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
       x: 474
       y: 891
       text: "cancel"
       anchors.rightMargin: 219
       anchors.bottomMargin: 116
       //Position the button in page1Container rectangle
       anchors.bottom:page1Container.bottom;
       anchors.right: page1Container.right

       onClicked: {
           currentobservation.uploadSaved();
           handlerLoader("mainMenu.qml")
       }

   }

   Connections
        {
       target: myLoader.item;
       onReturnData: {
           currentobservation.data = data
           currentobservation.location = "POINT(" + positionSource.position.coordinate.latitude + " " + positionSource.position.coordinate.longitude + ")"
           currentobservation.observer = options.observer
           currentobservation.server = options.server
           currentobservation.time = Qt.formatDateTime(new Date(), "yyyy-MM-dd")
           currentobservation.save();
           handlerLoader("mainMenu.qml")
       }
   }

   Button{
       id:buttonSave
       x: 224
       y: 891
       text: "save"
       anchors.rightMargin: 469
       anchors.bottomMargin: 116
       //Position the button in page1Container rectangle
       anchors.bottom:page1Container.bottom;
       anchors.right: page1Container.right

       onClicked: {
           Connections
                 {
               target: myLoader.item.getData();
                 }
       }
   }

}
