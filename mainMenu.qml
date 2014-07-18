import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id:top
        width:768
        height:1030
        color: "#d4d4d4"
        signal handlerLoader(string name, int index)



  Column {
          anchors.centerIn: parent
          spacing: parent.width / 10

          Button {
              id: continueButton
              width: 600
              height: 150

              text: "Continue with last template"
              onClicked: handlerLoader("Template_water.qml",0)
          }
          Button {
              id: selectTemplateButton
              width: 600
              height: 150
              text: "Select template"
              onClicked: handlerLoader("SelectTemplate.qml",0)
          }
          Button {
              id: downloadButton
              width: 600
              height: 150
              text: "Download template"

              onClicked: handlerLoader("DownloadTemplate.qml",0)
          }
      }
}
