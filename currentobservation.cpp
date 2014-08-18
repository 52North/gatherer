/****************************************************************************
** Copyright (C) 2014-2014 52°North Initiative for Geospatial Open Source
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
// This is the source file for the class CurrentObservation which handles everything about the current observation(s).
// Saving it, uploading it, deleting it, showing observations.

#include "currentobservation.h"
#include "dataobject.h"
#include <QNetworkReply>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QXmlStreamReader>

CurrentObservation::CurrentObservation(QObject *parent) :
    QObject(parent)
{
}

CurrentObservation::~CurrentObservation()
{
    delete nam;
}

/// To get the location of the current QML template
QString CurrentObservation::url() const
{
    return m_url;
}

/// To set the location of the current QML template
/// It also reads if there is a basemap, if so the map will be set up
void CurrentObservation::setUrl(const QString url)
{
    m_url = url;
    QStringList dirs = m_url.split("/");
    QStringList last = dirs[dirs.length() - 1].split(".");
    m_name = last[0];
    m_map = "";
    for (int i = 0;i<dirs.length() - 1;i++)
        m_map += dirs[i] + "/";
    m_map += m_name + ".png";

    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_name + ".gatherer";
    QString content;
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        content = stream.readAll();
    }
    file.close();

    QStringList metadata = content.split( "\n" );

    for (int i=1;i<metadata.length();i++){
        QStringList line = metadata[i].split("|");
        if (line.length() > 2)
            if (line[1] == "BaseMap"){
                QString mapUrl = line[2].trimmed();
                QStringList request = mapUrl.split("&");
                for (int j=0;j<request.length();j++){
                    if (request[j].startsWith("BBOX")){
                        QStringList parts = request[j].split("=");
                        QStringList coords = parts[1].split(",");
                        m_xmin = coords[0];
                        m_ymin = coords[1];
                        m_xmax = coords[2];
                        m_ymax = coords[3];
                    }
                    if (request[j].startsWith("WIDTH")){
                        QStringList parts = request[j].split("=");
                        m_width = parts[1];
                    }
                    if (request[j].startsWith("HEIGHT")){
                        QStringList parts = request[j].split("=");
                        m_height = parts[1];
                    }
                }
            }
    }
}

/// To get the name of the current template
QString CurrentObservation::name() const
{
    return m_name;
}

/// To set the name of the current template
void CurrentObservation::setName(const QString name)
{
    m_name = name;
}

/// To get the time of the current observation
QString CurrentObservation::time() const
{
    return m_time;
}

/// To set the time of the current observation
void CurrentObservation::setTime(const QString time)
{
    m_time = time;
}

/// To get the coordinates of the current observation
QString CurrentObservation::location() const
{
    return m_location;
}

/// To set the coordinates of the current observation
void CurrentObservation::setLocation(const QString location)
{
    m_location = location;
}

/// To get the name of the observer of the current observation
QString CurrentObservation::observer() const
{
    return m_observer;
}

/// to set the name of the observer of the current observation
void CurrentObservation::setObserver(const QString observer)
{
    m_observer = observer;
}

/// To get the data fields of the current observation
QString CurrentObservation::data() const
{
    return m_data;
}

/// To set the data fields of the current observation
void CurrentObservation::setData(const QString data)
{
    m_data = data;
}

/// To get the server url of the current observation
QString CurrentObservation::server() const
{
    return m_server;
}

/// To set the server url of the current observation
void CurrentObservation::setServer(const QString server)
{
    m_server = server;
}

/// To get the response of the server after the last upload
QString CurrentObservation::response() const
{
    return m_response;
}

/// To get the location of the image of the map of the current observation
QString CurrentObservation::map() const
{
    return m_map;
}

/// To get the xmin of the map of the current template
QString CurrentObservation::xmin() const
{
    return m_xmin;
}

/// To get the xmax of the map of the current template
QString CurrentObservation::xmax() const
{
    return m_xmax;
}

/// To get the ymin of the map of the current template
QString CurrentObservation::ymin() const
{
    return m_ymin;
}

/// To get the ymax of the map of the current template
QString CurrentObservation::ymax() const
{
    return m_ymax;
}

/// To get the width of the map of the current template
QString CurrentObservation::width() const
{
    return m_width;
}

/// To get the height of the map of the current template
QString CurrentObservation::height() const
{
    return m_height;
}

/// To upload the selected observation to the server.
void CurrentObservation::upload(int i)
{
    m_i = i;

    /// Reading the saved observations
    QFile saveFile(m_filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");

    /// Uploading the selected observation
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedUploadiSlot(QNetworkReply*)));
    qDebug() << observations[i];
    QUrl url(observations[i]);
    nam->get(QNetworkRequest(url));


}

/// The corresponding slot
void CurrentObservation::finishedUploadiSlot(QNetworkReply *reply)
{
    QString replyContent = reply->readAll();
    /// Saving the response
    if (replyContent.length() > 100) { /// if succes
        QStringList replyPieces = replyContent.split(">");
        QStringList response = replyPieces[3].split("<");
        m_response = response[0];
        /// deleting the uploaded observation
        QFile saveFile(m_filename);
        bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
        QString content;
        if( ret )
        {
            QTextStream stream(&saveFile);
            content = stream.readAll();
        }
        saveFile.close();
        QStringList observations = content.split("\n");
        QFile file(m_filename);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream stream(&file);
        for (int j = 0; j<observations.length()-1;j++){
            if (m_i != j)
                stream << observations[j] + "\n";
        }
        file.close();
    }
    else
        m_response = "upload failed";

    emit responseReady();
}

/// For saving the current observation
void CurrentObservation::save()
{
    /// Opening the savefile
    QFile saveFile(m_filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QString urlString = m_server + "?subjectobservation&location=" + m_location + "&time=" + m_time + "&subjectname=" + m_name + "&observer=" + m_observer + m_data + "\n";
        QTextStream stream(&saveFile);
        content = stream.readAll();
        /// Adding the observation at the end
        stream << urlString;
    }
    saveFile.close();
}

/// For uploading all the saved observations
void CurrentObservation::uploadSaved()
{
    m_i = 0;
    m_response = "";
    m_failed.clear();
    QFile saveFile(m_filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();

    QStringList observations = content.split("\n");

    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedUploadallSlot(QNetworkReply*)));
    qDebug() << observations[m_i];
    QUrl url(observations[m_i]);
    nam->get(QNetworkRequest(url));


}

/// The corresponding slot
void CurrentObservation::finishedUploadallSlot(QNetworkReply *reply)
{
    QString replyContent = reply->readAll();
    /// Saving response
    if (replyContent.length() > 100) {
        QStringList replyPieces = replyContent.split(">");
        QStringList response = replyPieces[3].split("<");
        m_response += response[0] + "\n";
    }
    else {
        m_response += "upload failed\n";
        m_failed.append(m_i);
    }
    //qDebug()<<replyContent;
    m_i++;
    /// loading in observations
    QFile saveFile(m_filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");

    if (m_i == observations.length() - 1){ /// last observation already uploaded, delete succesfull uploaded observations
        QFile file(m_filename);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream stream(&file);
        for (int j = 0; j<observations.length()-1;j++){
            if (m_failed.contains(j))
                stream << observations[j] + "\n";
        }
        file.close();
        emit responseReady();
    }
    else { /// upload next observation
        if ( nam)
            delete nam;

        nam = new QNetworkAccessManager();
        QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                         this, SLOT(finishedUploadallSlot(QNetworkReply*)));
        qDebug() << observations[m_i];
        QUrl url(observations[m_i]);
        nam->get(QNetworkRequest(url));
    }
}

/// For loading in the saved observations for the listmodel
void CurrentObservation::loadSaved()
{
    QFile saveFile(m_filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");
    m_model.clear();
    for (int i = 0; i<observations.length()-1;i++){
        QStringList data= observations[i].split("&");
        QStringList time = data[2].split("=");
        QStringList subjectname = data[3].split("=");
        QStringList input = data[5].split("=");
        m_model.append(new DataObject(time[1],subjectname[1],input[1]));
    }
}

/// Deleting the selected observation
void CurrentObservation::deleteObservation(int i)
{
    QFile saveFile(m_filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");
    QFile file(m_filename);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if( ret )
    {
        QTextStream stream(&file);
        for (int j = 0; j<observations.length()-1;j++){
            if (i != j)
                stream << observations[j] + "\n";
        }
    }
    file.close();
}

/// Check if there is a map downloaded
QString CurrentObservation::mapAvailable()
{
    QStringList filename = m_map.split("//");
    QFile file(filename[1]);
    QString result = "false";
    if (file.exists()) {
        result = "true";
        return result;
    }
    else
        return result;
}

/// To show the historical observations on the map.
void CurrentObservation::showObservations(const QString from, const QString to)
{
    /// Parse xml file
    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_name + ".xml";
    QFile file( filename );
    QDateTime fromDate = QDateTime::fromString(from, "yyyy-MM-dd");
    QDateTime toDate = QDateTime::fromString(to, "yyyy-MM-dd");
    QString time = "";
    QString observation = "";
    QString observer = "";
    QStringList coords = {"",""};
    if ( file.open(QIODevice::ReadWrite) )
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        bool firstObservation = false;
        bool secondObservation = false;
        while (!xmlReader.atEnd())
        {

            if (xmlReader.isStartElement())
            {
                QString name = xmlReader.name().toString();
                //qDebug()<< "start-tag: " + name;
                if (name == "Observation") {
                    if (firstObservation) {
                        observation = xmlReader.readElementText();
                        //qDebug()<< observation;
                    }
                    else
                        firstObservation = true;

                } else if (name == "Location") {
                    QString text = xmlReader.readElementText();
                    QString coord = text.mid(6, text.length() - 7);
                    coords = coord.split(" ");
                } else if (name == "TimeStamp") {
                    QString text = xmlReader.readElementText();
                    time = text.left(10);
                } else if (name == "Observer") {
                    observer = xmlReader.readElementText();
                }

            } else if (xmlReader.isEndElement()) {
                QString name = xmlReader.name().toString();
                if (name == "Observation")
                {
                    if (secondObservation)
                        secondObservation = false;
                    else {
                        firstObservation = false;
                        QDateTime timeDate = QDateTime::fromString(time, "yyyy-MM-dd");
                        if (timeDate <= toDate && timeDate >= fromDate)
                            emit addPoint(coords[0].toDouble(), coords[1].toDouble(), observation, time, observer, false);
                    }
                }
            }
            xmlReader.readNext();

        }
        if (xmlReader.hasError())
        {
            qDebug() << "XML error: " << xmlReader.errorString();
            qDebug() << firstObservation + " " + secondObservation;
        }
    }

    /// Parse new observations
    QFile saveFile(m_filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();

        saveFile.close();
        QStringList observations = content.split("\n");
        if (observations[0].startsWith("http"))
            for (int i = 0; i<observations.length()-1;i++){
                QStringList data= observations[i].split("&");
                QStringList coordData = data[1].split("=");
                QString coord = coordData[1].mid(6, coordData[1].length() - 7);
                coords = coord.split(" ");
                QStringList timeList = data[2].split("=");
                QStringList observerList = data[4].split("=");
                QStringList input = data[5].split("=");
                emit addPoint(coords[0].toDouble(), coords[1].toDouble(), input[1], timeList[1], observerList[1], true);
            }
    }
}


QQmlListProperty<DataObject> CurrentObservation::model()
{
    return QQmlListProperty<DataObject>(this,m_model);
}



