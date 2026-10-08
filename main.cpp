#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>

#include "ScryfallApi.h"
#include "DeckManager.h"

int main(int argc, char *argv[])
{
    std::cout << "App starting..." << std::endl;
    
    QGuiApplication app(argc, argv);
    std::cout << "QGuiApplication created" << std::endl;

    QQmlApplicationEngine engine;
    std::cout << "QQmlApplicationEngine created" << std::endl;

    ScryfallApi scryfallApi;
    DeckManager deckManager;

    engine.rootContext()->setContextProperty("ScryfallApi", &scryfallApi);
    engine.rootContext()->setContextProperty("DeckManager", &deckManager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {
            std::cerr << "QML object creation failed!" << std::endl;
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );

    std::cout << "Loading QML module..." << std::endl;
    engine.loadFromModule("mtgDeckBuilder", "Main");
    std::cout << "QML loaded, starting event loop..." << std::endl;

    return app.exec();
}
