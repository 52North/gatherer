#include <QtQuick/QQuickView>
#include <QApplication>
#include <QtQml>

#include "message.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    /*qmlRegisterType<Message>("Messages", 1, 0, "Message");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();
*/
    return app.exec();
}

