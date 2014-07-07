// MyItem.qml
import QtQuick 2.0
import Messages 1.0

//Message {
//    id: aMessage
//}

Text {
    width: 300; height: 300
    text: Message.author    // invokes Message::author() to get this value

    Component.onCompleted: {
        Message.author = "Jonah"  // invokes Message::setAuthor()
    }
}
