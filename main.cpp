#include "Core/DataGenerator.h"
#include "Core/MainController.h"
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

    qmlRegisterSingletonType(QUrl("qrc:/UiCore/AppStyle.qml"), "MovableComponents.UiCore", 1, 0, "AppStyle");

    const QUrl url(QStringLiteral("qrc:/View/main.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
