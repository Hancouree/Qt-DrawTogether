#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "socket.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Socket socket;

    engine.rootContext()->setContextProperty("Socket", &socket);

    const QUrl url(QStringLiteral("qrc:/Project/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
