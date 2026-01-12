#ifndef SOCKET_H
#define SOCKET_H

#include <QWebSocket>

#include "statemachine.h"
#include <requestmanager.h>

#define RECONNECT_INTERVAL_MS 3000
#define MAX_RECONNECT_ATTEMPTS 5

class Socket : public RequestManager
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected  NOTIFY connectionChanged)
    Q_PROPERTY(StateMachine::States state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged)
public:
    explicit Socket(QObject* parent = nullptr);
    ~Socket() override;
public slots:
    bool connected() const { return _connected; }
    StateMachine::States state() { return _state.getState(); };
    QString username() const { return _username; }

    void sendUsername(const QString& username);
    void searchRooms();
private slots:
    void onConnection();
    void onAnswer(const QString& answer);
signals:
    void connectionChanged();
    void stateChanged();
    void usernameChanged();
private:
    void initSocket();
    void initTimers();
    void initStateMachine();

    Request request(QJsonObject& json) override;
    void tryReconnect();

    //handlers

    StateMachine _state;

    QWebSocket* socket;
    bool _connected;
    QString session_id;
    QUrl serverUrl;

    QString _username;

    //QTimers
    QTimer reconnectTimer;
    int reconnectAttempts;
};

#endif // SOCKET_H
