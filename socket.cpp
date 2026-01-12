#include "socket.h"

Socket::Socket(QObject *parent) : RequestManager(parent), serverUrl(QUrl("wss://26.209.218.198:8080"))
{
    socket = new QWebSocket;

    initSocket();

    socket->open(serverUrl);

    initTimers();
    initStateMachine();
}

void Socket::initSocket()
{
    _connected = false;

    connect(socket, &QWebSocket::connected, this, &Socket::onConnection);
    connect(socket, &QWebSocket::textMessageReceived, this, &Socket::onAnswer);
    connect(socket, &QWebSocket::disconnected, this, [this]() {
        _connected = false;

        reconnectTimer.start(RECONNECT_INTERVAL_MS);
    });
    connect(socket, &QWebSocket::sslErrors, this, [this](const QList<QSslError> errors) {
        for (auto& error : errors)
            qDebug() << error.errorString() << '\n';

        socket->ignoreSslErrors();
    });
}

void Socket::initTimers()
{
    connect(&reconnectTimer, &QTimer::timeout, this, &Socket::tryReconnect);

}

void Socket::initStateMachine()
{
    connect(&_state, &StateMachine::stateChanged, this, [this]() {
        emit stateChanged();
    });
}

void Socket::onConnection()
{
    qDebug() << "Socket was connected to the server\n";
    _connected = true;
    _state.applyEvent(StateMachine::Events::STOP_WAITING);

    reconnectAttempts = 0;
    reconnectTimer.stop();
}

void Socket::onAnswer(const QString &message)
{
    qDebug() << message << '\n';
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isNull()) {
        qDebug() << "Invalid JSON\n";
        return;
    }

    QJsonObject root = doc.object();

    const RequestId requestId = root["requestId"].toInteger();

    if (requestId <= 0) {
        //...
    } else {
        requestDone(requestId, root);
    }
}

void Socket::tryReconnect()
{
    if (reconnectAttempts > MAX_RECONNECT_ATTEMPTS) {
        qDebug() << "MAX ATTEMPTS REACHED\n";
        //emit error;
        return;
    }

    qDebug() << "Reconnect attempt: " << reconnectAttempts << '\n';

    if (!serverUrl.isEmpty())
        socket->open(serverUrl);

    ++reconnectAttempts;
}

void Socket::sendUsername(const QString &username)
{
    QJsonObject json;

    json["cmd"] = "establish_username";
    json["username"] = username;
    json["timestamp"] = QDateTime::currentMSecsSinceEpoch();

    request(json)
    .done([this](const QJsonObject& root) {
        qDebug() << "answer caught in done method\n";

        _username = root["username"].toString();
        session_id = root["session_id"].toString();

        qDebug() << "username established\n";

        _state.applyEvent(StateMachine::Events::AUTHENTICATED);

        emit usernameChanged();
    })
    .fail([](QString error_message) {
            qDebug() << "Error: " << error_message << '\n';
    });
}

void Socket::searchRooms()
{
    QJsonObject json;

    json["cmd"] = "search_rooms";
    json["timestamp"] = QDateTime::currentMSecsSinceEpoch();
    json["session_id"] = session_id;

    qDebug() << json << '\n';

    // request(json)
    // .done([this](const QJsonObject& root) {
    //     // _state.applyEvent() //search rooms
    // });
}

Socket::~Socket()
{
    if (_connected) {
        socket->disconnect();
    }

    delete socket;
}

Request Socket::request(QJsonObject &json)
{
    json["requestId"] = ++next_id;

    setupTimer(next_id);
    socket->sendTextMessage(QJsonDocument(json).toJson());

    return Request(next_id, this);
}


