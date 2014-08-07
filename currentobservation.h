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
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

    QString name() const;
    void setName(const QString name);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    QString time() const;
    void setTime(const QString time);
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)

    QString location() const;
    void setLocation(const QString location);
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)

    QString observer() const;
    void setObserver(const QString observer);
    Q_PROPERTY(QString observer READ observer WRITE setObserver NOTIFY observerChanged)

    QString data() const;
    void setData(const QString data);
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)

    QString server() const;
    void setServer(const QString server);
    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)

    QString response() const;
    Q_PROPERTY(QString response READ response CONSTANT)

    QString map() const;
    Q_PROPERTY(QString map READ map CONSTANT)

    QString xmin() const;
    Q_PROPERTY(QString xmin READ xmin CONSTANT)

    QString xmax() const;
    Q_PROPERTY(QString xmax READ xmax CONSTANT)

    QString ymin() const;
    Q_PROPERTY(QString ymin READ ymin CONSTANT)

    QString ymax() const;
    Q_PROPERTY(QString ymax READ ymax CONSTANT)

    QString width() const;
    Q_PROPERTY(QString width READ width CONSTANT)

    QString height() const;
    Q_PROPERTY(QString height READ height CONSTANT)

    Q_INVOKABLE void upload();
    Q_INVOKABLE void upload(int i);
    Q_INVOKABLE void save();
    Q_INVOKABLE void uploadSaved();
    Q_INVOKABLE void loadSaved();
    Q_INVOKABLE void deleteObservation(int i);
    Q_INVOKABLE QString mapAvailable();
    Q_INVOKABLE void downloadObservations(QString from, QString to);
    Q_INVOKABLE void downloadObservations(QString from);
    Q_INVOKABLE void downloadObservations();
    Q_INVOKABLE void showObservations(const QString from, const QString to);

    QQmlListProperty<DataObject> model();
    Q_PROPERTY(QQmlListProperty<DataObject> model READ model CONSTANT)

signals:
    void responseReady();
    void addPoint(double lat, double lon, QString observation, QString time, QString observer);
    void urlChanged();
    void nameChanged();
    void timeChanged();
    void locationChanged();
    void observerChanged();
    void dataChanged();
    void serverChanged();

public slots:
    void finishedUploadSlot(QNetworkReply * reply);
    void finishedUploadiSlot(QNetworkReply * reply);
    void finishedUploadallSlot(QNetworkReply * reply);
    void finishedDownloadSlot(QNetworkReply * reply);

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
    QString m_map;
    QString m_xmin;
    QString m_xmax;
    QString m_ymin;
    QString m_ymax;
    QString m_height;
    QString m_width;
    QNetworkAccessManager* nam = 0;
    QString filename = "/data/data/org.qtproject.example.Gatherer/files/savedObservations.txt";//"/storage/emulated/0/Download/savedObservations.txt";
    int m_i;
    QList <int> m_failed;

};

#endif // CURRENTOBSERVATION_H
