import QtQuick 2.14
import QtQuick.Window 2.14
import com.mycompany.components 1.0
import MovableComponents.UiCore 1.0

Window {
    width: AppStyle.mainWindowWidth
    height: AppStyle.mainWindowHeight
    visible: true
    title: AppStyle.mainWindowTitleName

    id: window

    Item {
        id: backgroundItem
        anchors.fill: parent

        Rectangle {
            id: leftHalf
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width / 2
            color: AppStyle.mainWindowLeftColor
        }

        Rectangle {
            id: rightHalf
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width / 2
            color: AppStyle.mainWindowRightColor
        }
    }

    Component.onCompleted: {
        mainController.startAllGenerators();
    }

    Repeater {
        model: mainController.qmlComponents()

        delegate: DataRectangle {
            id: rectComponent
            x: modelData.x
            y: modelData.y
            width: AppStyle.componentWidth
            height: AppStyle.componentHeight
            color: modelData["color-hex"]

            property string dataSourceId: modelData.dataSource
            property var dataObject: dataGenerators.find(obj => obj.id === dataSourceId)

            text: rectComponent.x + width < window.width / 2 ? (dataObject ? modelData["id"] + ": " + dataObject.value : "xxxxx") : "xxxxx"

            SequentialAnimation on x {
                id : animationController
                running: true
                loops: Animation.Infinite

                property bool firstLoop: true

                NumberAnimation { from: firstLoop ? rectComponent.x : 0 ; to: window.width - rectComponent.width; duration: modelData["speed-msec"]; easing.type: Easing.Linear }
                NumberAnimation { from: window.width - rectComponent.width; to: 0; duration: modelData["speed-msec"]; easing.type: Easing.Linear }

                onRunningChanged: {
                    if (running && firstLoop) {
                        firstLoop = false
                    }
                }
            }

            onXChanged: {
                mainController.handleComponentPositionChanged(modelData.id, x + width);
            }
        }
    }
}
