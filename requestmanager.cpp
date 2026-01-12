#include "requestmanager.h"

RequestManager::RequestManager(QObject* parent) : QObject(parent) {}

void RequestManager::addDoneHandler(const RequestId &requestId, Handler handler)
{
    onDone.insert(std::pair<RequestId, Handler>(requestId, handler));
}

void RequestManager::addFailHandler(const RequestId &requestId, ErrorHandler handler)
{
    onFail.insert(std::pair<RequestId, ErrorHandler>(requestId, handler));
}

void RequestManager::setupTimer(const RequestId &requestId)
{
    if (!timers.contains(requestId)) {
        QTimer* timer = new QTimer;
        timer->setSingleShot(true);

        timers.insert(requestId, timer);
        connect(timer, &QTimer::timeout, this, [this, requestId]() {
            eraseTimer(requestId);

            requestFailed(requestId, "Request timeout, try later");
        });

        timer->start(TIMEOUT_INTERVAL);
    }
}

void RequestManager::eraseTimer(const RequestId &requestId)
{
    auto it = timers.find(requestId);
    if (it != timers.end()) {
        QTimer* timer = it.value();
        timers.erase(it);
        delete timer;
    }
}

void RequestManager::requestDone(const RequestId &requestId, QJsonObject &root)
{
    if (onDone.count(requestId)) {
        onDone[requestId](root);
        onDone.erase(requestId);
    }

    if (onFail.count(requestId))
        onFail.erase(requestId);

    eraseTimer(requestId);
}

void RequestManager::requestFailed(const RequestId &requestId, const QString &error_message)
{
    if (onFail.count(requestId)) {
        onFail[requestId](error_message);
        onFail.erase(requestId);
    }

    if (onDone.count(requestId))
        onDone.erase(requestId);

    eraseTimer(requestId);
}

RequestManager::~RequestManager() {
    for (auto it = timers.begin(); it != timers.end(); ) {
        auto* timer = it.value();
        it = timers.erase(it);
        delete timer;
    }
}

//REQUEST

Request::Request(const RequestId &requestId, RequestManager *manager) : requestId(requestId), manager(manager) {}

Request &Request::done(Handler callback)
{
    manager->addDoneHandler(requestId, callback);
    return *this;
}

Request &Request::fail(ErrorHandler callback)
{
    manager->addFailHandler(requestId, callback);
    return *this;
}

Request::~Request() {}
