import QtQuick 2.14
import QtQuick.Window 2.14
import com.mycompany.components 1.0

Window {
    width: 880
    height: 540
    visible: true
    title: "MovableComponents"

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
            color: "gray"
        }

        Rectangle {
            id: rightHalf
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width / 2
            color: "#FF4040"
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
            width: 110
            height: 50
            color: modelData["color-hex"]

            property string dataSourceId: modelData.dataSource
            property var dataObject: dataGenerators.find(obj => obj.id === dataSourceId)

            text: rectComponent.x + width < window.width / 2 ? (dataObject ? dataObject.value : "xxxxx") : "xxxxx"

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
