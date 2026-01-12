import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: "Draw Together"

    ConnectionPage {
        id: connectionPage
        visible: true
    }

    AuthenticationPage {
        id: authenticationPage
        visible: false
    }

    MenuPage {
        id: menuPage
        visible: false
    }

    StackView {
        id: stackView
        initialItem: connectionPage
        anchors.fill: parent
    }

    Connections {
        target: Socket

        function onStateChanged() {
            //delete stack view mb
            console.log(stackView.depth)
            switch(Socket.state) {
                case 0: //WAITING
                    stackView.replace(connectionPage)
                    break;
                case 1: //AUTHENTIFICATION
                    stackView.replace(authenticationPage)
                    break;
                case 2:
                    stackView.replace(menuPage)
                    break;
                default:
                    console.log("Default was called")
                    break;
            }
        }
    }

    Connections {
        target: authenticationPage

        function onSendUsername(username) {
            Socket.sendUsername(username)
        }
    }

    Connections {
        target: menuPage

        function onSearchRooms() {
            Socket.searchRooms();
        }

        function onCreateRoom() {
            // Socket.createRoom()
        }
    }
}
