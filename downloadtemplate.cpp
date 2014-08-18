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
// This is the source file for the class DownloadTemplate which handles everything about downloading templates, the basemap, historical observations and stores them.

#include "downloadtemplate.h"
#include <QTextStream>
#include <QFile>
#include <QDirIterator>
#include <QDebug>
#include "dataobject.h"
#include <QNetworkReply>
#include <QQuickView>
#include <QQmlListProperty>
#include <QList>

/// Constructor searches if there are already locally saved templates
DownloadTemplate::DownloadTemplate(QObject *parent) :
    QObject(parent)
{
    /// for testing
    //m_model.append(new DataObject("test", "file:///storage/emulated/0/Download/Template_LandUseMapping.qml"));
    //m_urls.append("file:///storage/emulated/0/Download/Template_LandUseMapping.qml");

    /// normal
    /// Reading the names from the namefile which correspond with the names of the template-files
    QString filenameNames= "/data/data/org.qtproject.example.Gatherer/files/names.txt";
    QFile fileNames( filenameNames );
    QString content;
    if ( fileNames.open(QIODevice::ReadWrite) )
    {
        QTextStream streamNames( &fileNames );
        content = streamNames.readAll();
    }
    fileNames.close();
    if (content != "") {
        QStringList templates = content.trimmed().split("\n");
        for (int i=0; i<templates.length(); i++){
            QStringList myTemplate = templates[i].split(":");
            m_templateNames.insert(myTemplate[0], myTemplate[1]);
        }
    }
    /// Finding the template files
    QDirIterator dirIt("/data/data/org.qtproject.example.Gatherer/files/",QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).suffix() == "qml"){
                QString filename= dirIt.filePath();
                QStringList folders = filename.split( "/" );
                QStringList nameAndExt = folders[folders.length() - 1].split(".");
                QString name = nameAndExt[0];
                m_model.append(new DataObject(m_templateNames[name], "file://" + filename));
                m_urls.append("file://" + filename);

            }

    }



}

DownloadTemplate::~DownloadTemplate()
{
    delete nam;
}

/// For testing, download file from downloads folder
void DownloadTemplate::download(const QString &templateName)
{
    QDirIterator dirIt2(templateName,QDirIterator::Subdirectories);
    while (dirIt2.hasNext()) {
        dirIt2.next();
        if (QFileInfo(dirIt2.filePath()).isFile())
            if (QFileInfo(dirIt2.filePath()).suffix() == "gatherer"){
                qDebug()<<dirIt2.filePath();

                QFile xmlString(dirIt2.filePath());
                bool ret = xmlString.open(QIODevice::ReadOnly | QIODevice::Text);
                if( ret )
                {
                    QTextStream stream(&xmlString);
                    QString content = stream.readAll();
                    QStringList pieces = content.split( "[-- end metadata --]" );

                    QStringList metadata = pieces[0].split( "\n" );
                    QString name = metadata[0];



                    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".qml";
                    QFile file( filename );
                    if ( file.open(QIODevice::ReadWrite) )
                    {
                        QTextStream stream( &file );
                        stream << pieces[1];
                    }
                    m_model.append(new DataObject(name, "file://" + filename));
                    m_urls.append("file://" + filename);

                }
            }
    }
}

/// For the templates list
QQmlListProperty<DataObject> DownloadTemplate::model()
{
    return QQmlListProperty<DataObject>(this,m_model);
}

/// To download a template from the server
void DownloadTemplate::downloadFromUrl(const QString & server, const QString &templateName)
{
    m_templateName = templateName;
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));
    QUrl url(server + "?subject=" + templateName);
    nam->get(QNetworkRequest(url));
}

/// The corresponding finished slot
void DownloadTemplate::finishedSlot(QNetworkReply *reply)
{
    QString content = reply->readAll();
    QStringList pieces = content.split( "[-- end metadata --]" );

    QStringList metadata = pieces[0].split( "\n" );
    QString name = metadata[0].trimmed();

    /// check if there is a basemap
    bool mapAvailable = false;
    for (int i=1;i<metadata.length();i++){
        QStringList line = metadata[i].split("|");
        if (line.length() > 2)
            if (line[1] == "BaseMap"){
                m_mapUrl = line[2].trimmed();
                mapAvailable = true;
            }
    }

    /// saving metadata
    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".gatherer";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << pieces[0];
    }
    file.close();

    /// saving qml template
    filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".qml";
    QFile file2( filename );
    if ( file2.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file2 );
        stream << pieces[1];
    }
    file2.close();

    /// saving name with spaces
    if (!m_templateNames.contains(m_templateName)){
        m_templateNames.insert(m_templateName, name);
        QString filenameNames= "/data/data/org.qtproject.example.Gatherer/files/names.txt";
        QFile fileNames( filenameNames );
        if ( fileNames.open(QIODevice::ReadWrite) )
        {
            QTextStream streamNames( &fileNames );
            content = streamNames.readAll();
            streamNames << m_templateName + ":" + name + "\n";
        }
        fileNames.close();
    }
    m_model.append(new DataObject(name, "file://" + filename));
    m_urls.append("file://" + filename);

    /// response to qml
    if (mapAvailable)
        emit downloadMap();
    else
        emit downloadObservationsSig();
}

/// To get the available templates on the server
void DownloadTemplate::getSubjectList(const QString & server)
{
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSubjectListSlot(QNetworkReply*)));
    QUrl url(server + "?subjectlist");
    nam->get(QNetworkRequest(url));
}

void DownloadTemplate::finishedSubjectListSlot(QNetworkReply *reply)
{
    QString content = reply->readAll();
    m_subjectslist = content.trimmed().split( ";" );
    m_subjects.clear();

    for (int i=0;i<m_subjectslist.length();i++){
        m_subjects.append(new DataObject(m_subjectslist[i], ""));
    }
    emit responseReady();
}

/// For the list of available templates
QQmlListProperty<DataObject> DownloadTemplate::subjectsModel()
{
    return QQmlListProperty<DataObject>(this,m_subjects);
}

/// to link template name with and without spaces
QString DownloadTemplate::templateName(const QString &name) const
{
    return m_templateNames[name];
}

/// to get the selected url of the template
QString DownloadTemplate::getUrl(const int & i) const
{
    return m_urls[i];
}

/// to get the name of the selected template to download
QString DownloadTemplate::getSubject(const int & i) const
{
    return m_subjectslist[i];
}


/// For downloading the basemap of the template if there is one
void DownloadTemplate::getMap()
{
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedMapSlot(QNetworkReply*)));
    QUrl url(m_mapUrl);
    nam->get(QNetworkRequest(url));
}

/// The corresponding slot
void DownloadTemplate::finishedMapSlot(QNetworkReply *reply)
{
   QImage* img = new QImage();
    img->loadFromData(reply->readAll());

    if(img->isNull())
        qDebug() << "oops";

    img->save("/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".png");
    emit downloadObservationsSig();
}

/// for testing
void DownloadTemplate::getMaps()
{
    qDebug() <<"aangeroepen";
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedMapSlots(QNetworkReply*)));
    QUrl url("http://130.89.222.201:8080/geoserver/wms?SERVICE=WMS&REQUEST=GetMap&VERSION=1.1&LAYERS=cite:itc_false_color_stdev25_tif_60cm&CRS=EPSG:4326&STYLES=&BBOX=6.877760913337248,52.21973335800224,6.892692511708865,52.226108841080546&WIDTH=1668&HEIGHT=1134&FORMAT=image/png");
    nam->get(QNetworkRequest(url));
}

/// for testing
void DownloadTemplate::finishedMapSlots(QNetworkReply *reply)
{
   qDebug() <<"ontvangen";
   QImage* img = new QImage();
    img->loadFromData(reply->readAll());

    if(img->isNull())
        qDebug() << "oops";

    img->save("/storage/emulated/0/Download/Template_LandUseMapping.png");
    qDebug() <<"gesaved";
}

/// For downloading the historical observations of a template
void DownloadTemplate::downloadObservations(const QString &server)
{
    if ( nam)
        delete nam;

    QString urlString = server + "?subjectquery=" + m_templateName;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedObservationsSlot(QNetworkReply*)));
    QUrl url(urlString);
    nam->get(QNetworkRequest(url));
}

/// The corresponding slot to save them as xml
void DownloadTemplate::finishedObservationsSlot(QNetworkReply *reply)
{
    QString content = reply->readAll();
    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".xml";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << content;
    }
    file.close();
    emit responseReady();
}
