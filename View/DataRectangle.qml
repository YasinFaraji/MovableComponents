import QtQuick 2.14
import MovableComponents.UiCore 1.0

Rectangle {
    property alias text: textItem.text

    border.color: AppStyle.rectangleBorderColor
    border.width: AppStyle.rectangleBorderWidth
    radius: AppStyle.rectangleRadius

    Text {
        id: textItem
        anchors.centerIn: parent
        font.pixelSize: AppStyle.rectangleFontSize
        color: AppStyle.rectangleTextColor
    }
}
