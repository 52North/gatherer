import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id:top
        width:768
        height:1030
        color: "#d4d4d4"
        signal handlerLoader(string name)



  Column {
          anchors.centerIn: parent
          spacing: parent.width / 10

          Button {
              id: continueButton
              width: 600
              height: 150

              text: "Continue with last template"
              onClicked: handlerLoader("Observation.qml")
          }
          Button {
              id: selectTemplateButton
              width: 600
              height: 150
              text: "Select template"
              onClicked: handlerLoader("SelectTemplate.qml")
          }
          Button {
              id: downloadButton
              width: 600
              height: 150
              text: "Download template"

              onClicked: handlerLoader("DownloadTemplate.qml")
          }
          Button {
              id: observationsButton
              width:600
              height: 150
              text: "Saved observations"

              onClicked: handlerLoader("SavedObservations.qml")
          }
      }
}
