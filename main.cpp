#include <QtQuick/QQuickView>
#include <QApplication>
#include <QtQml>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtAndroidExtras>

#include "message.h"
#include "dataobject.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

/*    QQmlApplicationEngine engine;

    qmlRegisterType<Message>("Messages", 1, 0, "Message");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();
*/

    QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getFilesDir", "()Ljava/io/File;");
    /*QAndroidJniObject mediaPath = mediaDir.callObjectMethod("getAbsolutePath", "()Ljava/lang/String;" );
    QAndroidJniEnvironment env;
    if (env->ExceptionCheck()) {
            // Handle exception here.
            env->ExceptionClear();
    }*/

    //QStringList nameFilter("Template_*.qml");

    QString dataValue = mediaDir.toString();
     qDebug() << dataValue;

    /*QDirIterator dirIt("qrc:",QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).suffix() == "qml")
                qDebug()<<dirIt.filePath();
    }*/
    QList<QObject*> dataList;
    dataList.append(new DataObject("Water access points", "Template_water.qml"));
    dataList.append(new DataObject("Animal observation", "Template_animal.qml"));

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("myModel", QVariant::fromValue(dataList));
//![0]

    view.setSource(QUrl("qrc:main.qml"));
    view.show();

    //engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    return app.exec();
}

