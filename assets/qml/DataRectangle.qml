import QtQuick 2.14

Rectangle {
    property alias text: textItem.text

    border.color: "black"
    border.width: 1
    radius: 10

    Text {
        id: textItem
        anchors.centerIn: parent
        font.pixelSize: 20
        color: "white"
    }
}
