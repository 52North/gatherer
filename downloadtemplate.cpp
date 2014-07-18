#include "downloadtemplate.h"
#include <QTextStream>
#include <QFile>
#include <QDirIterator>
#include <QDebug>
#include "dataobject.h"
#include <QNetworkReply>

DownloadTemplate::DownloadTemplate(QObject *parent) :
    QObject(parent)
{
    m_model.append(new DataObject("Water access points", "Template_water.qml"));
    m_model.append(new DataObject("Animal observation", "Template_animal.qml"));

}

DownloadTemplate::~DownloadTemplate()
{
    delete nam;
}

void DownloadTemplate::download(const QString &templateName)
{
    QDirIterator dirIt2(templateName,QDirIterator::Subdirectories); // "/storage/emulated/0/Download/"
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
                    //qDebug()<<pieces[1];

                    QStringList metadata = pieces[0].split( "\n" );
                    QString name = metadata[0];
                    QString filename= "/storage/emulated/0/Download/" + name + ".qml";
                    QFile file( filename );
                    if ( file.open(QIODevice::ReadWrite) )
                    {
                        QTextStream stream( &file );
                        stream << pieces[1];
                    }
                    m_model.append(new DataObject(name, "file://" + filename));

                }
            }
    }
}

void DownloadTemplate::downloadFromUrl(const QString &templateName)
{
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));
    QUrl url("http://130.89.222.201:8090/gatherer?template=" + templateName);
    nam->get(QNetworkRequest(url));
}

QQmlListProperty<DataObject> DownloadTemplate::model()
{
    return QQmlListProperty<DataObject>(this,m_model);
}

void DownloadTemplate::finishedSlot(QNetworkReply *reply)
{
    QString content = reply->readAll();
    QStringList pieces = content.split( "[-- end metadata --]" );
    //qDebug()<<pieces[1];

    QStringList metadata = pieces[0].split( "\n" );
    QString name = metadata[0];
    QString filename= "/storage/emulated/0/Download/" + name + ".qml";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << pieces[1];
    }
    m_model.append(new DataObject(name, "file://" + filename));
}
