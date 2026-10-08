#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScryfallApi.h"
#include "DeckManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ScryfallApi scryfallApi;
    DeckManager deckManager;

    engine.rootContext()->setContextProperty(
        "ScryfallApi",
        &scryfallApi
        );

    engine.rootContext()->setContextProperty(
        "DeckManager",
        &deckManager
        );

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []()
        {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    engine.loadFromModule("mtgDeckBuilder", "Main");

    return app.exec();
}