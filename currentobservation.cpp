#include "currentobservation.h"
#include "dataobject.h"
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

QString CurrentObservation::url() const
{
    return m_url;
}

void CurrentObservation::setUrl(const QString url)
{
    m_url = url;
    QStringList dirs = m_url.split("/");
    QStringList last = dirs[dirs.length() - 1].split(".");
    m_name = last[0];
}

QString CurrentObservation::name() const
{
    return m_name;
}

void CurrentObservation::setName(const QString name)
{
    m_name = name;
}

QString CurrentObservation::time() const
{
    return m_time;
}

void CurrentObservation::setTime(const QString time)
{
    m_time = time;
}

QString CurrentObservation::location() const
{
    return m_location;
}

void CurrentObservation::setLocation(const QString location)
{
    m_location = location;
}

QString CurrentObservation::observer() const
{
    return m_observer;
}

void CurrentObservation::setObserver(const QString observer)
{
    m_observer = observer;
}

QString CurrentObservation::data() const
{
    return m_data;
}

void CurrentObservation::setData(const QString data)
{
    m_data = data;
}

QString CurrentObservation::server() const
{
    return m_server;
}

void CurrentObservation::setServer(const QString server)
{
    m_server = server;
}

QString CurrentObservation::response() const
{
    return m_response;
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

void CurrentObservation::upload(int i)
{
    m_i = i;
    QFile saveFile(filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");

    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedUploadiSlot(QNetworkReply*)));
    qDebug() << observations[i];
    QUrl url(observations[i]);
    nam->get(QNetworkRequest(url));


}

void CurrentObservation::save()
{
    QFile saveFile(filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QString urlString = m_server + "?subjectobservation&location=" + m_location + "&time=" + m_time + "&subjectname=" + m_name + "&observer=" + m_observer + m_data + "\n";
        QTextStream stream(&saveFile);
        content = stream.readAll();
        stream << urlString;
    }
    saveFile.close();
}

void CurrentObservation::uploadSaved()
{
    m_i = 0;
    m_response = "";
    m_failed.clear();
    QFile saveFile(filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();

    QStringList observations = content.split("\n");

    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedUploadallSlot(QNetworkReply*)));
    qDebug() << observations[m_i];
    QUrl url(observations[m_i]);
    nam->get(QNetworkRequest(url));


}

void CurrentObservation::loadSaved()
{
    QFile saveFile(filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");
    m_model.clear();
    for (int i = 0; i<observations.length()-1;i++){
        //http://130.89.222.201:8095/gatherer?subjectobservation&location=POINT(51.9803661 5.6791265)&time=2014-07-28&subjectname=LanduseMapping&observer=henk&field1=Urban Fabric
        QStringList data= observations[i].split("&");
        QStringList time = data[2].split("=");
        QStringList subjectname = data[3].split("=");
        QStringList input = data[5].split("=");
        m_model.append(new DataObject(time[1],subjectname[1],input[1]));
    }
}

void CurrentObservation::deleteObservation(int i)
{
    QFile saveFile(filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if( ret )
    {
        QTextStream stream(&file);
        for (int j = 0; j<observations.length()-1;j++){
            if (i != j)
                stream << observations[j] + "\n";
        }
    }
    file.close();
}

QQmlListProperty<DataObject> CurrentObservation::model()
{
    return QQmlListProperty<DataObject>(this,m_model);
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

void CurrentObservation::finishedUploadiSlot(QNetworkReply *reply)
{
    QString replyContent = reply->readAll();
    if (replyContent.length() > 100) {
        QStringList replyPieces = replyContent.split(">");
        QStringList response = replyPieces[3].split("<");
        m_response = response[0];
        qDebug()<<replyContent;
        QFile saveFile(filename);
        bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
        QString content;
        if( ret )
        {
            QTextStream stream(&saveFile);
            content = stream.readAll();
        }
        saveFile.close();
        QStringList observations = content.split("\n");
        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream stream(&file);
        for (int j = 0; j<observations.length()-1;j++){
            if (m_i != j)
                stream << observations[j] + "\n";
        }
        file.close();
    }
    else
        m_response = "upload failed";

    emit responseReady();
}

void CurrentObservation::finishedUploadallSlot(QNetworkReply *reply)
{
    QString replyContent = reply->readAll();
    if (replyContent.length() > 100) {
        QStringList replyPieces = replyContent.split(">");
        QStringList response = replyPieces[3].split("<");
        m_response += response[0] + "\n";
    }
    else {
        m_response += "upload failed\n";
        m_failed.append(m_i);
    }
    qDebug()<<replyContent;
    m_i++;
    QFile saveFile(filename);
    bool ret = saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content;
    if( ret )
    {
        QTextStream stream(&saveFile);
        content = stream.readAll();
    }
    saveFile.close();
    QStringList observations = content.split("\n");

    if (m_i == observations.length() - 1){
        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream stream(&file);
        for (int j = 0; j<observations.length()-1;j++){
            if (m_failed.contains(j))
                stream << observations[j] + "\n";
        }
        file.close();
        emit responseReady();
    }
    else {
        if ( nam)
            delete nam;

        nam = new QNetworkAccessManager();
        QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                         this, SLOT(finishedUploadallSlot(QNetworkReply*)));
        qDebug() << observations[m_i];
        QUrl url(observations[m_i]);
        nam->get(QNetworkRequest(url));
    }


}

