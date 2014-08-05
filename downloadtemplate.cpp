#include "downloadtemplate.h"
#include <QTextStream>
#include <QFile>
#include <QDirIterator>
#include <QDebug>
#include "dataobject.h"
#include <QNetworkReply>
#include <QQuickView>
#include <QQmlListProperty>
#include <QList>

DownloadTemplate::DownloadTemplate(QObject *parent) :
    QObject(parent)
{
    m_model.append(new DataObject("test", "file:///storage/emulated/0/Download/Template_LandUseMapping.qml"));
    m_urls.append("file:///storage/emulated/0/Download/Template_LandUseMapping.qml");
    QString filenameNames= "/data/data/org.qtproject.example.Gatherer/files/names.txt";
    QFile fileNames( filenameNames );
    QString content;
    if ( fileNames.open(QIODevice::ReadWrite) )
    {
        QTextStream streamNames( &fileNames );
        content = streamNames.readAll();
    }
    fileNames.close();
    if (content != "") {
        QStringList templates = content.trimmed().split("\n");
        for (int i=0; i<templates.length(); i++){
            QStringList myTemplate = templates[i].split(":");
            m_templateNames.insert(myTemplate[0], myTemplate[1]);
        }
    }
    QDirIterator dirIt("/data/data/org.qtproject.example.Gatherer/files/",QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).suffix() == "qml"){
                QString filename= dirIt.filePath();
                QStringList folders = filename.split( "/" );
                QStringList nameAndExt = folders[folders.length() - 1].split(".");
                QString name = nameAndExt[0];
                m_model.append(new DataObject(m_templateNames[name], "file://" + filename));
                m_urls.append("file://" + filename);

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
                    m_urls.append("file://" + filename);

                }
            }
    }
}

void DownloadTemplate::downloadFromUrl(const QString & server, const QString &templateName)
{
    m_templateName = templateName;
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));
    QUrl url(server + "?subject=" + templateName);
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

    bool mapAvailable = false;

    for (int i=1;i<metadata.length();i++){
        QStringList line = metadata[i].split("|");
        if (line.length() > 2)
            if (line[1] == "BaseMap"){
                m_mapUrl = line[2].trimmed();
                mapAvailable = true;
                emit downloadMap();
            }
    }

    QString filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".gatherer";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << pieces[0];
    }
    file.close();

    filename= "/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".qml";
    QFile file2( filename );
    if ( file2.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file2 );
        stream << pieces[1];
    }
    file2.close();

    if (!m_templateNames.contains(m_templateName)){
        m_templateNames.insert(m_templateName, name);
        QString filenameNames= "/data/data/org.qtproject.example.Gatherer/files/names.txt";
        QFile fileNames( filenameNames );
        if ( fileNames.open(QIODevice::ReadWrite) )
        {
            QTextStream streamNames( &fileNames );
            content = streamNames.readAll();
            streamNames << m_templateName + ":" + name + "\n";
        }
        fileNames.close();
    }
    m_model.append(new DataObject(name, "file://" + filename));
    m_urls.append("file://" + filename);
    if (!mapAvailable)
        emit responseReady();
}

void DownloadTemplate::getSubjectList(const QString & server)
{
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSubjectListSlot(QNetworkReply*)));
    QUrl url(server + "?subjectlist");
    nam->get(QNetworkRequest(url));
}

void DownloadTemplate::finishedSubjectListSlot(QNetworkReply *reply)
{
    QString content = reply->readAll();
    m_subjectslist = content.trimmed().split( ";" );
    m_subjects.clear();

    for (int i=0;i<m_subjectslist.length();i++){
        //qDebug()<<m_subjectslist[i];
        m_subjects.append(new DataObject(m_subjectslist[i], ""));
    }
    responseReady();
}

QQmlListProperty<DataObject> DownloadTemplate::subjectsModel()
{
    return QQmlListProperty<DataObject>(this,m_subjects);
}

QString DownloadTemplate::templateName(const QString &name) const
{
    return m_templateNames[name];
}

QString DownloadTemplate::getUrl(const int & i) const
{
    //    DataObject test1 = new DataObject();
    //    const DataObject test = m_model.value(i, test1);
    return m_urls[i];
}

QString DownloadTemplate::getSubject(const int & i) const
{
    return m_subjectslist[i];
}

void DownloadTemplate::getMap()
{
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedMapSlot(QNetworkReply*)));
    QUrl url(m_mapUrl);
    nam->get(QNetworkRequest(url));
}


void DownloadTemplate::finishedMapSlot(QNetworkReply *reply)
{
   QImage* img = new QImage();
    img->loadFromData(reply->readAll());

    if(img->isNull())
        qDebug() << "oops";

    img->save("/data/data/org.qtproject.example.Gatherer/files/" + m_templateName + ".png");
    emit responseReady();
}

void DownloadTemplate::getMaps()
{
    qDebug() <<"aangeroepen";
    if ( nam)
        delete nam;

    nam = new QNetworkAccessManager();
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedMapSlots(QNetworkReply*)));
    QUrl url("http://130.89.222.201:8080/geoserver/wms?SERVICE=WMS&REQUEST=GetMap&VERSION=1.1&LAYERS=cite:itc_false_color_stdev25_tif_60cm&CRS=EPSG:4326&STYLES=&BBOX=6.877760913337248,52.21973335800224,6.892692511708865,52.226108841080546&WIDTH=1668&HEIGHT=1134&FORMAT=image/png");
    nam->get(QNetworkRequest(url));
}


void DownloadTemplate::finishedMapSlots(QNetworkReply *reply)
{
   qDebug() <<"ontvangen";
   QImage* img = new QImage();
    img->loadFromData(reply->readAll());

    if(img->isNull())
        qDebug() << "oops";

    img->save("/storage/emulated/0/Download/Template_LandUseMapping.png");
    qDebug() <<"gesaved";
}
