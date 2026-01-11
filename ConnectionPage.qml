import QtQuick
import QtQuick.Controls

Item {
    id: root

    Column {
        width: Math.max(busyIndicator.width, text.implicitWidth)
        height: busyIndicator.height + text.implicitHeight
        anchors.centerIn: parent
        spacing: 10

        Item {
            id: busyIndicator
            width: 50
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: spinner
                width: 30
                height: 30
                anchors.centerIn: parent
                radius: width / 2
                color: "transparent"
                border.width: 3
                border.color: "lightgray"

                Rectangle {
                    width: 3
                    height: 15
                    color: "blue"
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        top: parent.top
                    }
                }

                RotationAnimator on rotation {
                    from: 0
                    to: 360
                    duration: 1000
                    loops: Animation.Infinite
                    running: true
                }
            }
        }

        Text {
            id: text
            text: "Подключаемся к серверу!"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
