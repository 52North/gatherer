#ifndef DOWNLOADTEMPLATE_H
#define DOWNLOADTEMPLATE_H

#include <QObject>
#include <QQmlListProperty>
#include <QNetworkAccessManager>

class DataObject;
class QNetworkReply;


class DownloadTemplate : public QObject
{
    Q_OBJECT
public:
    explicit DownloadTemplate(QObject *parent = 0);
    ~DownloadTemplate();
    Q_INVOKABLE void download(const QString & templateName);
    Q_INVOKABLE void downloadFromUrl(const QString & templateName);
    QQmlListProperty<DataObject> model();

    Q_PROPERTY(QQmlListProperty<DataObject> model READ model CONSTANT)

signals:

private:
    QList<DataObject *> m_model;
    QNetworkAccessManager* nam = 0;

public slots:
    void finishedSlot(QNetworkReply * reply);

};

#endif // DOWNLOADTEMPLATE_H
