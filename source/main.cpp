#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <backend.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    Backend backend;
    engine.rootContext()->setContextProperty("backend", &backend);

    engine.load("qrc:/main.qml");
    return app.exec();
}
