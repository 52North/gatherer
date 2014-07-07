import QtQuick 1.1

Item {id:top
    width:300
    height:200
    Loader{id:window}
    signal handlerLoader(string name, int index)
    Loader {
        id:pageLoader
        source:"Page1.qml"
    }
    Connections {
        target:pageLoader.item
        onHandlerLoader:{pageLoader.source=name;
            if(index===2)
                window.source="NewWindow.qml";
        }
    }
}
