import QtQuick
import QtQuick.Controls

Item {
    id: root

    signal searchRooms();
    signal createRoom();

    Column {
        id: column
        width: Math.max(searchRooms.width, createRoom.width)
        height: searchRooms.height + createRoom.height
        anchors.centerIn: parent

        Button {
            id: searchRooms
            text: "Найти комнату"
            width: Math.min(root.width * 0.6, 500)
            height: 35

            onClicked: root.searchRooms();
        }

        Button {
            id: createRoom
            text: "Создать комнату"
            width: Math.min(root.width * 0.6, 500)
            height: 35

            onClicked: root.createRoom()
        }
    }
}
