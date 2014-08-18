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
// This is the header file for the class Options which stores the global settings (server address, observer name and last used template).

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>

class Options : public QObject
{
    Q_OBJECT
public:
    explicit Options(QObject *parent = 0);

    QString server();
    void setServer(QString server);
    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)

    QString observer();
    void setObserver(QString observer);
    Q_PROPERTY(QString observer READ observer WRITE setObserver NOTIFY observerChanged)

    QString current();
    void setCurrent(QString current);
    Q_PROPERTY(QString current READ current WRITE setCurrent NOTIFY currentChanged)

    Q_INVOKABLE void save();

signals:
    void serverChanged();
    void observerChanged();
    void currentChanged();

public slots:

private:
    QString m_server;
    QString m_observer;
    QString m_current;
};

#endif // OPTIONS_H
