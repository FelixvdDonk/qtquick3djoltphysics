#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../shared/shared.h"
#include "examplesteplistener.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    registerSharedTypes();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
