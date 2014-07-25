#include "currentobservation.h"
#include <QNetworkReply>
#include <QFile>
#include <QTextStream>

CurrentObservation::CurrentObservation(QObject *parent) :
    QObject(parent)
{
}

CurrentObservation::~CurrentObservation()
{
    delete nam;
}

QString CurrentObservation::url()
{
    return m_url;
}

void CurrentObservation::setUrl(QString url)
{
    m_url = url;
    QStringList dirs = m_url.split("/");
    QStringList last = dirs[dirs.length() - 1].split(".");
    m_name = last[0];
}

QString CurrentObservation::name()
{
    return m_name;
}

void CurrentObservation::setName(QString name)
{
    m_name = name;
}

QString CurrentObservation::time()
{
    return m_time;
}

void CurrentObservation::setTime(QString time)
{
    m_time = time;
}

QString CurrentObservation::location()
{
    return m_location;
}

void CurrentObservation::setLocation(QString location)
{
    m_location = location;
}

QString CurrentObservation::observer()
{
    return m_observer;
}

void CurrentObservation::setObserver(QString observer)
{
    m_observer = observer;
}

QString CurrentObservation::data()
{
    return m_data;
}

void CurrentObservation::setData(QString data)
{
    m_data = data;
}

QString CurrentObservation::server()
{
    return m_server;
}

void CurrentObservation::setServer(QString server)
{
    m_server = server;
}

void CurrentObservation::upload()
{
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedUploadSlot(QNetworkReply*)));
    QString urlString = m_server + "?subjectobservation&location=" + m_location + "&time=" + m_time + "&subjectname=" + m_name + "&observer=" + m_observer + m_data;
    qDebug() << urlString;
    QUrl url(urlString);
    nam->get(QNetworkRequest(url));
}

void CurrentObservation::save()
{
    QFile saveFile("/data/data/org.qtproject.example.Gatherer/files/savedObservations.txt");
    bool ret = saveFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    QString urlString = "\n" + m_server + "?subjectobservation&location=" + m_location + "&time=" + m_time + "&subjectname=" + m_name + "&observer=" + m_observer + m_data;

    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << content + urlString;
    }
}

void CurrentObservation::finishedUploadSlot(QNetworkReply *reply)
{
    QString content = reply->readAll();
    //QStringList subjects = content.split( ";" );
    qDebug()<<content;
//    m_subjects.clear();

//    for (int i=0;i<subjects.length();i++){
//        m_subjects.append(new DataObject(subjects[i], ""));
//    }
//    responseReady();
}
