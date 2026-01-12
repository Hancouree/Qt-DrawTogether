#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

#define TIMEOUT_INTERVAL 500

class Request;

using Handler = std::function<void(QJsonObject&)>;
using ErrorHandler = std::function<void(QString)>;
using RequestId =  quint64;

class RequestManager : public QObject
{
public:
    RequestManager(QObject* parent = nullptr);
    virtual ~RequestManager();

    void addDoneHandler(const RequestId& requestId, Handler handler);
    void addFailHandler(const RequestId& requestId, ErrorHandler handler);

    virtual Request request(QJsonObject& json) = 0; //think later about it
protected:
    void setupTimer(const RequestId& requestId);
    void eraseTimer(const RequestId& requestId);
    void requestDone(const RequestId& requestId, QJsonObject& root);
    void requestFailed(const RequestId& requestId, const QString& error_message);

    std::map<RequestId, Handler> onDone;
    std::map<RequestId, ErrorHandler> onFail;
    QHash<RequestId, QTimer*> timers;
    std::atomic<int> next_id{0};
};

class Request {
public:
    Request(const RequestId& requestId, RequestManager* manager);
    ~Request();

    Request& done(Handler callback);
    Request& fail(ErrorHandler callback);
private:
    RequestId requestId;
    RequestManager* manager;
};


#endif // REQUESTMANAGER_H
