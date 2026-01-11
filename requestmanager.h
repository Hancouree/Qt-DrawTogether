#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>


class Request;

using Handler = std::function<void(QJsonObject&)>;
using RequestId =  quint64;

class RequestManager : public QObject
{
public:
    RequestManager(QObject* parent = nullptr);
    ~RequestManager();

    void addDoneHandler(const RequestId& requestId, Handler handler);
    void addFailHandler(const RequestId& requestId, Handler handler);

    virtual Request request(QJsonObject& json) = 0; //think later about it

protected:
    std::map<RequestId, Handler> onDone;
    std::map<RequestId, Handler> onFail;
    std::atomic<int> next_id{0};
};

class Request {
public:
    Request(const RequestId& requestId, RequestManager* manager);
    ~Request();

    Request& done(Handler callback);
    Request& fail(Handler callback);
private:
    RequestId requestId;
    RequestManager* manager;
};


#endif // REQUESTMANAGER_H
