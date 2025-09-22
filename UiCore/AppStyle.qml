pragma Singleton
import QtQuick 2.14

QtObject {
    readonly property string rectangleBorderColor: "black"
    readonly property int rectangleBorderWidth: 1
    readonly property int rectangleRadius: 10
    readonly property int rectangleFontSize: 20
    readonly property string rectangleTextColor: "white"

    readonly property int mainWindowWidth: 880
    readonly property int mainWindowHeight: 540
    readonly property string mainWindowTitleName: "MovableComponents"
    readonly property string mainWindowLeftColor: "gray"
    readonly property string mainWindowRightColor: "#FF4040"

    readonly property int componentWidth: 130
    readonly property int componentHeight: 50
}
