/****************************************************************************
** Copyright (C) 2014-2014 52�North Initiative for Geospatial Open Source
** Software GmbH
**
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License version 2 as published
** by the Free Software Foundation.
**
** If the program is linked with libraries which are licensed under one of
** the following licenses, the combination of the program with the linked
** library is not considered a "derivative work" of the program:
**
**  - Apache License, version 2.0
**  - Apache Software License, version 1.0
**  - GNU Lesser General Public License, version 3
**  - Mozilla Public License, versions 1.0, 1.1 and 2.0
**  - Common Development and Distribution License (CDDL), version 1.0.
**
** Therefore the distribution of the program linked with libraries licensed
** under the aforementioned licenses, is permitted by the copyright holders
** if the distribution is compliant with both the GNU General Public
** icense version 2 and the aforementioned licenses.
**
** This program is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
** Public License for more details.
****************************************************************************/

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

