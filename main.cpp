// main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "todolistmodel.h"

int main(int argc, char *argv[]) {
    // Klargjør applikasjonen
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);

    // Registrer klassen for QML
    TodoListModel todoList;
    engine.rootContext()->setContextProperty("todoModel", &todoList);

    // Start applikasjonen
    engine.load(url);
    return app.exec();
}
