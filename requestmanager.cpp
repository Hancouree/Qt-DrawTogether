#include "requestmanager.h"

RequestManager::RequestManager(QObject* parent) : QObject(parent) {}

void RequestManager::addDoneHandler(const RequestId &requestId, Handler handler)
{
    onDone.insert(std::pair<RequestId, Handler>(requestId, handler));
}

void RequestManager::addFailHandler(const RequestId &requestId, Handler handler)
{
    onFail.insert(std::pair<RequestId, Handler>(requestId, handler));
}


RequestManager::~RequestManager() {}

//REQUEST

Request::Request(const RequestId &requestId, RequestManager *manager) : requestId(requestId), manager(manager) {}

Request &Request::done(Handler callback)
{
    manager->addDoneHandler(requestId, callback);
    return *this;
}

Request &Request::fail(Handler callback)
{
    manager->addFailHandler(requestId, callback);
    return *this;
}

Request::~Request() {}
