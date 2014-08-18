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
// This is the source file for the class Options which stores the global settings (server address, observer name and last used template).

#include <QFile>
#include <QDirIterator>
#include <QTextStream>
#include <QDebug>
#include "options.h"

Options::Options(QObject *parent) :
    QObject(parent)
{
    /// standard values
    m_server = "http://130.89.222.201:8095/gatherer";
    m_observer = "henk";
    m_current = "not";

    /// Check if there are saved settings
    QDirIterator dirIt("/data/data/org.qtproject.example.Gatherer/files/",QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).suffix() == "ini"){
                QString filename= dirIt.filePath();
                QStringList folders = filename.split( "/" );
                QStringList nameAndExt = folders[folders.length() - 1].split(".");
                QString name = nameAndExt[0];
                if (name == "options"){
                    QFile optionsFile(dirIt.filePath());
                    bool ret = optionsFile.open(QIODevice::ReadOnly | QIODevice::Text);
                    if( ret )
                    {
                        QTextStream stream(&optionsFile);
                        QString content = stream.readAll();
                        QStringList options = content.split(";");
                        m_server = options[0];
                        m_observer = options[1];
                        m_current = options[2];
                    }
                }
            }
    }
}


QString Options::server()
{
    return m_server;
}

void Options::setServer(QString server)
{
    m_server = server;
}

QString Options::observer()
{
    return m_observer;
}

void Options::setObserver(QString observer)
{
    m_observer = observer;
}

QString Options::current()
{
    return m_current;
}

void Options::setCurrent(QString current)
{
    m_current = current;
}

/// Save the current settings to file
void Options::save()
{
    QString filename= "/data/data/org.qtproject.example.Gatherer/files/options.ini";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << m_server + ";" + m_observer + ";" + m_current;
    }
}
