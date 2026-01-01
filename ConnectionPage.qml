import QtQuick
import QtQuick.Controls

Item {
    id: root

    Column {
        width: Math.max(busyIndicator.width, text.implicitWidth)
        height: logo.implicitHeight + busyIndicator.height + text.implicitHeight
        anchors.centerIn: parent
        spacing: 10

        Text {
            id: logo
            text: "Draw Together"
            font.pixelSize: 20
            font.weight: 550
            anchors.horizontalCenter: parent.horizontalCenter
        }

        BusyIndicator {
            id: busyIndicator
            width: 50
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: text
            text: "Подключаемся к серверу!"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
