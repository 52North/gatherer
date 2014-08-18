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
// This is the header file for the class DataObject which stores data for list models.

#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString time READ time CONSTANT)
    Q_PROPERTY(QString subjectname READ subjectname CONSTANT)
    Q_PROPERTY(QString data READ data CONSTANT)

public:
    DataObject(QObject *parent=0);
    DataObject(const QString &name, const QString &url, QObject *parent=0);
    DataObject(const QString &time, const QString &subjectname, const QString &data, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString url() const;
    void setUrl(const QString &url);

    QString time() const;

    QString subjectname() const;

    QString data() const;

signals:
    void nameChanged();
    void urlChanged();

private:
    QString m_name;
    QString m_url;
    QString m_time;
    QString m_subjectname;
    QString m_data;
};


#endif
