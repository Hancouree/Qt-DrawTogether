import QtQuick
import QtQuick.Controls

Item {
    id: root

    signal sendUsername(string username)

    Column {
        width: Math.max(text.implicitWidth, textField.width)
        height: text.implicitHeight + textField.height + button.height
        anchors.centerIn: parent
        spacing: 20

        Text {
            id: text
            text: "Выберите себе никнейм"
            font.pixelSize: 24
            font.weight: 600
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField {
            id: textField
            width: Math.min(root.width * 0.6, 500)
            height: 35
            placeholderText: "Введите сюда"
            anchors.horizontalCenter: parent.horizontalCenter

            background: Rectangle {
                border.width: 1
                border.color: "black"
                radius: 5
                // verticalCenter: Text.verticalCenter
            }
        }

        Button {
            id: button
            width: Math.min(root.width * 0.6, 500)
            height: 35
            text: !isClicked ? "Отправить" : ""
            anchors.horizontalCenter: parent.horizontalCenter
            enabled: !isClicked

            property bool isClicked: false

            BusyIndicator {
                property int size: Math.min(button.width, button.height) - 5
                width: size
                height: size
                visible: parent.isClicked
                running: parent.isClicked
                anchors.centerIn: parent
            }

            onClicked: {
                const username = textField.text.trim()
                if (username.length !== 0) {
                    root.sendUsername(username)
                    textField.text = ""
                    isClicked = true
                }
            }

        }
    }
}
