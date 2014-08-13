// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This is the start of an observation, it has one or two tabs. Record observation and map.

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
        tabPosition: controlPage.item ? controlPage.item.tabPosition : Qt.TopEdge
        anchors.fill: parent
        anchors.margins: 2

        Tab {
            id: controlPage
            title: "Observation"
            active: true
            Observation { }

            Component.onCompleted: {
                if (currentobservation.mapAvailable() === "true"){
                    frame.addTab("Map", Qt.createComponent("Map.qml"))
                    frame.moveTab(0,1)
                }
            }
        }
    }

}

