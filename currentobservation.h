#ifndef CURRENTOBSERVATION_H
#define CURRENTOBSERVATION_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QQmlListProperty>

class QNetworkReply;
class DataObject;

class CurrentObservation : public QObject
{
    Q_OBJECT
public:
    explicit CurrentObservation(QObject *parent = 0);
    ~CurrentObservation();

    QString url() const;
    void setUrl(const QString url);
    Q_PROPERTY(QString url READ url WRITE setUrl)

    QString name() const;
    void setName(const QString name);
    Q_PROPERTY(QString name READ name WRITE setName)

    QString time() const;
    void setTime(const QString time);
    Q_PROPERTY(QString time READ time WRITE setTime)

    QString location() const;
    void setLocation(const QString location);
    Q_PROPERTY(QString location READ location WRITE setLocation)

    QString observer() const;
    void setObserver(const QString observer);
    Q_PROPERTY(QString observer READ observer WRITE setObserver)

    QString data() const;
    void setData(const QString data);
    Q_PROPERTY(QString data READ data WRITE setData)

    QString server() const;
    void setServer(const QString server);
    Q_PROPERTY(QString server READ server WRITE setServer)

    QString response() const;
    Q_PROPERTY(QString response READ response CONSTANT)

    Q_INVOKABLE void upload();
    Q_INVOKABLE void upload(int i);
    Q_INVOKABLE void save();
    Q_INVOKABLE void uploadSaved();
    Q_INVOKABLE void loadSaved();
    Q_INVOKABLE void deleteObservation(int i);

    QQmlListProperty<DataObject> model();
    Q_PROPERTY(QQmlListProperty<DataObject> model READ model CONSTANT)

signals:
    void responseReady();

public slots:
    void finishedUploadSlot(QNetworkReply * reply);
    void finishedUploadiSlot(QNetworkReply * reply);
    void finishedUploadallSlot(QNetworkReply * reply);

private:
    QList<DataObject *> m_model;
    QList<QString> m_urls;
    QString m_url;
    QString m_name;
    QString m_time;
    QString m_location;
    QString m_observer;
    QString m_data;
    QString m_server;
    QString m_response;
    QNetworkAccessManager* nam = 0;
    QString filename = "/data/data/org.qtproject.example.Gatherer/files/savedObservations.txt";//"/storage/emulated/0/Download/savedObservations.txt";
    int m_i;
    QList <int> m_failed;

};

#endif // CURRENTOBSERVATION_H
