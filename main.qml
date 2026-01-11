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

    StackView {
        id: stackView
        initialItem: connectionPage
        anchors.fill: parent
    }

    Connections {
        target: Socket

        function onStateChanged() {
            //delete stack view mb
            console.log(Socket.state)
            switch(Socket.state) {
                case 0: //CONNECTING
                    stackView.push(connectionPage)
                    break;
                case 3: //AUTHENTIFICATION
                    stackView.pop()
                    stackView.push(authenticationPage)
                    break;
                case 2:
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
}
