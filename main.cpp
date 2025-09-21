#include "DataGenerator.h"
#include "MainController.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<DataGenerator>("com.mycompany.components", 1, 0, "DataGenerator");

    MainController mainController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mainController", &mainController);
    engine.rootContext()->setContextProperty("dataGenerators", mainController.dataGenerators());

    const QUrl url(QStringLiteral("qrc:/assets/qml/main.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
