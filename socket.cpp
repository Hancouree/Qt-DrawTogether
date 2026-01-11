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
    _state.applyEvent(StateMachine::Events::CONNECTION_ESTABLISHED);

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

    if (onDone.count(requestId)) {
        onDone[requestId](root);
        onDone.erase(requestId);
    }

    if (onFail.count(requestId))
        onFail.erase(requestId);
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

        _state.applyEvent(StateMachine::Events::AUTHENTICATION_SUCCESS);

        emit usernameChanged();
    })
    .fail([](const QJsonObject& root) {
            qDebug() << "Error ocurred\n";
    });
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

    socket->sendTextMessage(QJsonDocument(json).toJson());

    return Request(next_id, this);
}


