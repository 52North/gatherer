#include <QFile>
#include <QDirIterator>
#include <QTextStream>
#include <QDebug>
#include "options.h"

Options::Options(QObject *parent) :
    QObject(parent)
{
    m_server = "http://130.89.222.201:8095/gatherer";
    m_observer = "henk";
    QDirIterator dirIt("/data/data/org.qtproject.example.Gatherer/files/",QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).suffix() == "ini"){
                qDebug()<<dirIt.filePath();

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

void Options::save()
{
    QString filename= "/data/data/org.qtproject.example.Gatherer/files/options.ini";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << m_server + ";" + m_observer;
    }
}
