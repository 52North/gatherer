#include "currentobservation.h"
#include "dataobject.h"
#include <QNetworkReply>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QXmlStreamReader>

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
    m_map = "";
    for (int i = 0;i<dirs.length() - 1;i++)
        m_map += dirs[i] + "/";
    m_map += m_name + ".png";

    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_name + ".gatherer";
    QString content;
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        content = stream.readAll();
    }
    file.close();

    QStringList metadata = content.split( "\n" );
    QString name = metadata[0].trimmed();

    for (int i=1;i<metadata.length();i++){
        QStringList line = metadata[i].split("|");
        if (line.length() > 2)
            if (line[1] == "BaseMap"){
                QString mapUrl = line[2].trimmed();
                QStringList request = mapUrl.split("&");
                for (int j=0;j<request.length();j++){
                    if (request[j].startsWith("BBOX")){
                        QStringList parts = request[j].split("=");
                        QStringList coords = parts[1].split(",");
                        m_xmin = coords[0];
                        m_ymin = coords[1];
                        m_xmax = coords[2];
                        m_ymax = coords[3];
                    }
                    if (request[j].startsWith("WIDTH")){
                        QStringList parts = request[j].split("=");
                        m_width = parts[1];
                    }
                    if (request[j].startsWith("HEIGHT")){
                        QStringList parts = request[j].split("=");
                        m_height = parts[1];
                    }
                }
            }
    }
} // http://130.89.222.201:8080/geoserver/wms?
//SERVICE=WMS&
//REQUEST=GetMap&
//VERSION=1.1&
//LAYERS=cite:itc_false_color_stdev25_tif_60cm&
//CRS=EPSG:32632&
//STYLES=&
//BBOX=355049.7,5787599.8,356050.5,5788280.3&
//WIDTH=1668&
//HEIGHT=1134&
//FORMAT=image/png

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

QString CurrentObservation::map() const
{
    return m_map;
}

QString CurrentObservation::xmin() const
{
    return m_xmin;
}

QString CurrentObservation::xmax() const
{
    return m_xmax;
}

QString CurrentObservation::ymin() const
{
    return m_ymin;
}

QString CurrentObservation::ymax() const
{
    return m_ymax;
}

QString CurrentObservation::width() const
{
    return m_width;
}

QString CurrentObservation::height() const
{
    return m_height;
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

QString CurrentObservation::mapAvailable()
{
    QStringList filename = m_map.split("//");
    QFile file(filename[1]);
    QString result = "false";
    if (file.exists()) {
        result = "true";
        return result;
    }
    else
        return result;
}

void CurrentObservation::downloadObservations(QString from, QString to)
{
    if ( nam)
        delete nam;

    QString urlString = m_server + "?subjectquery=" + m_name + "&begintime=" + from + "&endtime=" + to + "&envelope=" + m_ymax + "," + m_xmin + "," + m_ymin + "," + m_xmax;


    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedDownloadSlot(QNetworkReply*)));
    QUrl url(urlString);
    nam->get(QNetworkRequest(url));
}

void CurrentObservation::downloadObservations(QString from)
{
    if ( nam)
        delete nam;

    QString urlString = m_server + "?subjectquery=" + m_name + "&begintime=" + from + "&envelope=" + m_ymax + "," + m_xmin + "," + m_ymin + "," + m_xmax;


    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedDownloadSlot(QNetworkReply*)));
    QUrl url(urlString);
    nam->get(QNetworkRequest(url));
}

void CurrentObservation::downloadObservations()
{
    if ( nam)
        delete nam;

    QString urlString = m_server + "?subjectquery=" + m_name + "&envelope=" + m_ymax + "," + m_xmin + "," + m_ymin + "," + m_xmax;


    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedDownloadSlot(QNetworkReply*)));
    QUrl url(urlString);
    nam->get(QNetworkRequest(url));
}

void CurrentObservation::finishedDownloadSlot(QNetworkReply *reply)
{
    const QString content = reply->readAll();

    QXmlStreamReader xmlReader (content);
    xmlReader.readNext();
    bool firstObservation = false;
    bool secondObservation = false;
    //Reading from the file
    QString time = "";
    QString observation = "";
    QString observer = "";
    QStringList coords = {"",""};
    while (!xmlReader.atEnd())
    {

        if (xmlReader.isStartElement())
        {
            QString name = xmlReader.name().toString();
            //qDebug()<< "start-tag: " + name;
            if (name == "Observation") {
                if (firstObservation) {
                    //secondObservation = true;
                    observation = xmlReader.readElementText();
                    //qDebug()<< observation;
                }
                else
                    firstObservation = true;

            } else if (name == "Location") {
                QString text = xmlReader.readElementText();
                QString coord = text.mid(6, text.length() - 7);
                coords = coord.split(" ");
            } else if (name == "TimeStamp") {
                QString text = xmlReader.readElementText();
                time = text.left(10);
                //qDebug()<< time;
            } else if (name == "Observer") {
                observer = xmlReader.readElementText();
                //qDebug()<< observer;
            }

        } else if (xmlReader.isEndElement()) {
            QString name = xmlReader.name().toString();
            //qDebug()<< "end-tag: " + name;
            if (name == "Observation")
            {
                if (secondObservation)
                    secondObservation = false;
                else {
                    firstObservation = false;
                    emit addPoint(coords[0].toDouble(), coords[1].toDouble(), observation, time, observer);
                }
            }
        }
        xmlReader.readNext();

    }
    if (xmlReader.hasError())
    {
        qDebug() << "XML error: " << xmlReader.errorString();
        qDebug() << firstObservation + " " + secondObservation;
    }

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

