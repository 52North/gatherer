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
    Q_INVOKABLE void getSubjectList();

    QQmlListProperty<DataObject> model();
    QQmlListProperty<DataObject> subjectsModel();

    Q_PROPERTY(QQmlListProperty<DataObject> model READ model CONSTANT)
    Q_PROPERTY(QQmlListProperty<DataObject> subjectsModel READ subjectsModel CONSTANT)

signals:
    void responseReady();

private:
    QList<DataObject *> m_model;
    QList<DataObject *> m_subjects;
    QNetworkAccessManager* nam = 0;

public slots:
    void finishedSlot(QNetworkReply * reply);
    void finishedSubjectListSlot(QNetworkReply * reply);

};

#endif // DOWNLOADTEMPLATE_H
