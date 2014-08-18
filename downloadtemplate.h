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
// This is the header file for the class DownloadTemplate which handles everything about downloading templates, the basemap, historical observations and stores them.

#ifndef DOWNLOADTEMPLATE_H
#define DOWNLOADTEMPLATE_H

#include <QObject>
#include <QQmlListProperty>
#include <QNetworkAccessManager>

class DataObject;
class QNetworkReply;


class DownloadTemplate : public QObject
{
    Q_OBJECT
public:
    explicit DownloadTemplate(QObject *parent = 0);
    ~DownloadTemplate();

    Q_INVOKABLE void download(const QString & templateName);
    Q_INVOKABLE void downloadFromUrl(const QString & server, const QString & templateName);
    Q_INVOKABLE void getSubjectList(const QString & server);
    Q_INVOKABLE QString getUrl(const int & i) const;
    Q_INVOKABLE QString getSubject(const int & i) const;
    Q_INVOKABLE QString templateName(const QString & name) const;
    Q_INVOKABLE void getMap();
    Q_INVOKABLE void downloadObservations(const QString & server);

    Q_INVOKABLE void getMaps();

    QQmlListProperty<DataObject> model();
    QQmlListProperty<DataObject> subjectsModel();

    Q_PROPERTY(QQmlListProperty<DataObject> model READ model CONSTANT)
    Q_PROPERTY(QQmlListProperty<DataObject> subjectsModel READ subjectsModel CONSTANT)


signals:
    void responseReady();
    void downloadMap();
    void downloadObservationsSig();

private:
    QList<DataObject *> m_model;
    QList<DataObject *> m_subjects;
    QNetworkAccessManager* nam = 0;
    QString m_templateName;
    QString m_mapUrl;
    QList<QString> m_urls;
    QStringList m_subjectslist;
    QHash<QString, QString> m_templateNames;

public slots:
    void finishedSlot(QNetworkReply * reply);
    void finishedSubjectListSlot(QNetworkReply * reply);
    void finishedMapSlot(QNetworkReply * reply);
    void finishedMapSlots(QNetworkReply * reply);
    void finishedObservationsSlot(QNetworkReply * reply);

};

#endif // DOWNLOADTEMPLATE_H
