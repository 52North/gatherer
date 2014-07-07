import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id:top
        width: 384
        height:640
        signal handlerLoader(string name, int index)



  Column {
          anchors.centerIn: parent
          spacing: parent.width / 6

          Button {
              id: hospitalButton
              width: 200
              height: 50

              text: "Water access points"
              onClicked: handlerLoader("Water.qml",0)
          }
          Button {
              id: savanneButton
              text: "Animal observations"
              onClicked: console.log(savanneButton.text + " clicked")
          }
          Button {
              id: healthButton
              text: "Health risks"

              onClicked: console.log(healthButton.text + " clicked")
          }
      }
}
