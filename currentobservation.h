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
// This is the header file for the class CurrentObservation which handles everything about the current observation(s).
// Saving it, uploading it, deleting it, showing observations.

#ifndef CURRENTOBSERVATION_H
#define CURRENTOBSERVATION_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QQmlListProperty>

class QNetworkReply;
class DataObject;

class CurrentObservation : public QObject
{
    Q_OBJECT
public:
    explicit CurrentObservation(QObject *parent = 0);
    ~CurrentObservation();

    QString url() const;
    void setUrl(const QString url);
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

    QString name() const;
    void setName(const QString name);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    QString time() const;
    void setTime(const QString time);
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)

    QString location() const;
    void setLocation(const QString location);
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)

    QString observer() const;
    void setObserver(const QString observer);
    Q_PROPERTY(QString observer READ observer WRITE setObserver NOTIFY observerChanged)

    QString data() const;
    void setData(const QString data);
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)

    QString server() const;
    void setServer(const QString server);
    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)

    QString response() const;
    Q_PROPERTY(QString response READ response CONSTANT)

    QString map() const;
    Q_PROPERTY(QString map READ map CONSTANT)

    QString xmin() const;
    Q_PROPERTY(QString xmin READ xmin CONSTANT)

    QString xmax() const;
    Q_PROPERTY(QString xmax READ xmax CONSTANT)

    QString ymin() const;
    Q_PROPERTY(QString ymin READ ymin CONSTANT)

    QString ymax() const;
    Q_PROPERTY(QString ymax READ ymax CONSTANT)

    QString width() const;
    Q_PROPERTY(QString width READ width CONSTANT)

    QString height() const;
    Q_PROPERTY(QString height READ height CONSTANT)

    Q_INVOKABLE void upload(int i);
    Q_INVOKABLE void save();
    Q_INVOKABLE void uploadSaved();
    Q_INVOKABLE void loadSaved();
    Q_INVOKABLE void deleteObservation(int i);
    Q_INVOKABLE QString mapAvailable();
    Q_INVOKABLE void showObservations(const QString from, const QString to);

    QQmlListProperty<DataObject> model();
    Q_PROPERTY(QQmlListProperty<DataObject> model READ model CONSTANT)

signals:
    void responseReady();
    void addPoint(double lat, double lon, QString observation, QString time, QString observer, bool newObservation);
    void urlChanged();
    void nameChanged();
    void timeChanged();
    void locationChanged();
    void observerChanged();
    void dataChanged();
    void serverChanged();

public slots:
    void finishedUploadiSlot(QNetworkReply * reply);
    void finishedUploadallSlot(QNetworkReply * reply);

private:
    QList<DataObject *> m_model;
    QList<QString> m_urls;
    QString m_url;
    QString m_name;
    QString m_time;
    QString m_location;
    QString m_observer;
    QString m_data;
    QString m_server;
    QString m_response;
    QString m_map;
    QString m_xmin;
    QString m_xmax;
    QString m_ymin;
    QString m_ymax;
    QString m_height;
    QString m_width;
    QNetworkAccessManager* nam = 0;
    QString m_filename = "/data/data/org.qtproject.example.Gatherer/files/savedObservations.txt";//"/storage/emulated/0/Download/savedObservations.txt";
    int m_i;
    QList <int> m_failed;

};

#endif // CURRENTOBSERVATION_H
