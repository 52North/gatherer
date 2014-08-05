import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {id:page1Container
    width: 768
    height: 1030
    color: "#d4d4d4"
    signal handlerLoader(string name)

    Connections {
        target: controlPage.item
        onHandlerLoader:{handlerLoader(name);
        }

    }

    TabView {
        id:frame
        //enabled: enabledCheck.checked
        tabPosition: controlPage.item ? controlPage.item.tabPosition : Qt.TopEdge
        anchors.fill: parent
        anchors.margins: 2

        Tab {
            id: controlPage
            title: "Observation"
            active: true
            Observation { }
            //            Component.onCompleted: {
            //                frame.moveTab(0,1)
            //            }
            Component.onCompleted: {
                if (currentobservation.mapAvailable() === "true"){
                    frame.addTab("Map", Qt.createComponent("Map.qml"))
                    frame.moveTab(0,1)
                }
            }
        }
    }

}

