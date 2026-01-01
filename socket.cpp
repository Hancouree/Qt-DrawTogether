#include "socket.h"

inline Socket::STATES transition(const Socket::STATES& state, const Socket::EVENTS& event) {
    if (event == Socket::DISCONNECTED) {
        return Socket::RECONNECTING;
    }

    switch(state) {
    case Socket::CONNECTING:
        if (event == Socket::CONNECTED)
            return Socket::AUTHENTICATION;
    case Socket::AUTHENTICATION:
        if (event == Socket::USERNAME_ESTABLISHED)
            return Socket::MENU;
    default:
        return state;
    }

    return state;
}

Socket::Socket(QObject *parent) : QObject(parent),
    currentState(CONNECTING)
{
    socket = new QWebSocket;

    socket->open(QUrl("wss://26.209.218.198:8080"));

    connect(socket, &QWebSocket::connected, this, &Socket::onConnection);
    connect(socket, &QWebSocket::sslErrors, this, [this](const QList<QSslError> errors) {
        for (auto& error : errors)
            qDebug() << error.errorString() << '\n';

        socket->ignoreSslErrors();
    });
}

void Socket::onConnection()
{
    qDebug() << "Socket was connected to the server\n";
    currentState = transition(currentState, CONNECTED);
    emit stateChanged();
}

Socket::STATES Socket::state()
{
    return currentState;
}

QString Socket::username()
{
    return _username;
}

void Socket::sendServerRequest(const QString &req)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->sendTextMessage(req); //создать QTimer::singleshot()
    } else {
        //...
    }
}

void Socket::sendUsername(const QString &username)
{
    QJsonObject json;

    json["cmd"] = "establish_username";
    json["username"] = username;
    json["timestamp"] = QDateTime::currentMSecsSinceEpoch();

    sendServerRequest(QJsonDocument(json).toJson());
}

//handlers
bool Socket::handleEstablishedUsername(const QString& answer, QJsonObject& root) {
    if (answer != "username_established")
        return false;

    _username = root["username"].toString();
    session_id = root["session_id"].toString();

    currentState = transition(currentState, USERNAME_ESTABLISHED);

    usernameChanged();
    stateChanged();

    return true;
}

Socket::~Socket()
{
    delete socket;
}

