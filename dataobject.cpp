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
// This is the source file for the class DataObject which stores data for list models.

#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
{
}

/// Constructor for the lists of templates
DataObject::DataObject(const QString &name, const QString &url, QObject *parent)
    : QObject(parent), m_name(name), m_url(url)
{
}

/// Constructor for the list of observations
DataObject::DataObject(const QString &time, const QString &subjectname, const QString &data, QObject *parent)
    : QObject(parent), m_time(time), m_subjectname(subjectname), m_data(data)
{

}

QString DataObject::name() const
{
    return m_name;
}

void DataObject::setName(const QString &name)
{
    m_name = name;
}

QString DataObject::url() const
{
    return m_url;
}

void DataObject::setUrl(const QString &url)
{
    m_url = url;
}

QString DataObject::time() const
{
    return m_time;
}

QString DataObject::subjectname() const
{
    return m_subjectname;
}

QString DataObject::data() const
{
    return m_data;
}

