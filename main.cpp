#include <QtQuick/QQuickView>
#include <QApplication>
#include <QtQml>
#include <QQmlComponent>
#include <QQmlContext>

#include <string>
#include <fstream>
#include <streambuf>

#include "qtquickcontrolsapplication.h"
#include <QtQml/QQmlApplicationEngine>

#include "message.h"
#include "dataobject.h"
#include "downloadtemplate.h"


int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);

    /*qmlRegisterType<Message>("Messages", 1, 0, "Message");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();
*/

    QtQuickControlsApplication app(argc, argv);
    QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));


    qDebug() << QDir::currentPath();

    //QQuickView view;
   // view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctxt = engine.rootContext();
    qmlRegisterType<DownloadTemplate>("DownloadTemplate",1,0,"DownloadTemplate");
    qmlRegisterType<DataObject>("DataObject",1,0,"DataObject");
    DownloadTemplate downloadTemplate;
    ctxt->setContextProperty("downloadtemplate", &downloadTemplate);
    //![0]



    //view.setSource(QUrl("qrc:main.qml"));
    //view.show();

    //engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    return app.exec();
}

