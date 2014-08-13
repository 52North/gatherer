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
