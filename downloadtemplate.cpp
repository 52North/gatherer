#include "downloadtemplate.h"
#include <QTextStream>
#include <QFile>
#include <QDirIterator>
#include <QDebug>
#include "dataobject.h"
#include <QNetworkReply>
#include <QQuickView>

DownloadTemplate::DownloadTemplate(QObject *parent) :
    QObject(parent)
{
    QDirIterator dirIt("/data/data/org.qtproject.example.Gatherer/files/",QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).suffix() == "qml"){
                qDebug()<<dirIt.filePath();

                QString filename= dirIt.filePath();
                QStringList folders = filename.split( "/" );
                QStringList nameAndExt = folders[folders.length() - 1].split(".");
                QString name = nameAndExt[0];
                m_model.append(new DataObject(name, "file://" + filename));


            }

    }

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
                    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".qml";
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
    m_templateName = templateName;
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));
    QUrl url("http://130.89.222.201:8095/gatherer?subject=" + templateName);
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
    QString name = metadata[0].trimmed();
    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".qml";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << pieces[1];
    }
    m_model.append(new DataObject(name, "file://" + filename));
}

void DownloadTemplate::getSubjectList()
{
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSubjectListSlot(QNetworkReply*)));
    QUrl url("http://130.89.222.201:8095/gatherer?subjectlist");
    nam->get(QNetworkRequest(url));
}

void DownloadTemplate::finishedSubjectListSlot(QNetworkReply *reply)
{
    QString content = reply->readAll();
    QStringList subjects = content.split( ";" );
    //qDebug()<<pieces[1];
    m_subjects.clear();

    for (int i=0;i<subjects.length();i++){
        m_subjects.append(new DataObject(subjects[i], ""));
    }
    responseReady();
}

QQmlListProperty<DataObject> DownloadTemplate::subjectsModel()
{
    return QQmlListProperty<DataObject>(this,m_subjects);
}
