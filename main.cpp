// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This is the main source file. It sets up the gui (QML) application and initiates the c++ classes which are connected to the QML context.

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

#include "dataobject.h"
#include "downloadtemplate.h"
#include "currentobservation.h"
#include "options.h"


int main(int argc, char *argv[])
{
    /// Making a QML application
    QtQuickControlsApplication app(argc, argv);
    QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));

    //qDebug() << QDir::currentPath();

    /// Connecting the c++ classes to the QML context
    QQmlContext *ctxt = engine.rootContext();
    qmlRegisterType<DownloadTemplate>("DownloadTemplate",1,0,"DownloadTemplate");
    qmlRegisterType<CurrentObservation>("CurrentObservation",1,0,"CurrentObservation");
    qmlRegisterType<DownloadTemplate>("Options",1,0,"Options");
    qmlRegisterType<DataObject>("DataObject",1,0,"DataObject");
    DownloadTemplate downloadTemplate;
    CurrentObservation currentObservation;
    Options options;
    ctxt->setContextProperty("downloadtemplate", &downloadTemplate);
    ctxt->setContextProperty("currentobservation", &currentObservation);
    ctxt->setContextProperty("options", &options);

    return app.exec();
}

