#ifndef SOCKET_H
#define SOCKET_H

#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

class Socket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(STATES state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged)
public:
    enum STATES {
        CONNECTING,
        RECONNECTING,
        AUTHENTICATION,
        MENU,
        ROOM
    };
    Q_ENUM(STATES)

    enum EVENTS {
        CONNECTED,
        DISCONNECTED,
        USERNAME_ESTABLISHED,
    };
    Q_ENUM(EVENTS)

    Socket(QObject* parent = nullptr);
    ~Socket();
public slots:
    STATES state();
    QString username();

    void sendUsername(const QString& username);
private slots:
    void onConnection();
signals:
    void stateChanged();
    void usernameChanged();
private:
    void sendServerRequest(const QString& req);

    //handlers
    bool handleEstablishedUsername(const QString& answer, QJsonObject& root);

    STATES currentState;
    QWebSocket* socket;
    QString _username;
    QString session_id;
};

#endif // SOCKET_H
