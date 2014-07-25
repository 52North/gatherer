#ifndef CURRENTOBSERVATION_H
#define CURRENTOBSERVATION_H

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkReply;

class CurrentObservation : public QObject
{
    Q_OBJECT
public:
    explicit CurrentObservation(QObject *parent = 0);
    ~CurrentObservation();

    QString url();
    void setUrl(QString url);
    Q_PROPERTY(QString url READ url WRITE setUrl)

    QString name();
    void setName(QString name);
    Q_PROPERTY(QString name READ name WRITE setName)

    QString time();
    void setTime(QString time);
    Q_PROPERTY(QString time READ time WRITE setTime)

    QString location();
    void setLocation(QString location);
    Q_PROPERTY(QString location READ location WRITE setLocation)

    QString observer();
    void setObserver(QString observer);
    Q_PROPERTY(QString observer READ observer WRITE setObserver)

    QString data();
    void setData(QString data);
    Q_PROPERTY(QString data READ data WRITE setData)

    QString server();
    void setServer(QString server);
    Q_PROPERTY(QString server READ server WRITE setServer)

    Q_INVOKABLE void upload();
    Q_INVOKABLE void save();

signals:

public slots:
    void finishedUploadSlot(QNetworkReply * reply);

private:
    QString m_url;
    QString m_name;
    QString m_time;
    QString m_location;
    QString m_observer;
    QString m_data;
    QString m_server;
    QNetworkAccessManager* nam = 0;

};

#endif // CURRENTOBSERVATION_H
