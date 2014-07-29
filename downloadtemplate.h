#ifndef DOWNLOADTEMPLATE_H
#define DOWNLOADTEMPLATE_H

#include <QObject>
#include <QQmlListProperty>
#include <QNetworkAccessManager>
#include <QVariantList>

class DataObject;
class QNetworkReply;


class DownloadTemplate : public QObject
{
    Q_OBJECT
public:
    explicit DownloadTemplate(QObject *parent = 0);
    ~DownloadTemplate();

    Q_INVOKABLE void download(const QString & templateName);
    Q_INVOKABLE void downloadFromUrl(const QString & server, const QString & templateName);
    Q_INVOKABLE void getSubjectList(const QString & server);
    Q_INVOKABLE QString getUrl(const int & i) const;
    Q_INVOKABLE QString getSubject(const int & i) const;
    Q_INVOKABLE QString templateName(const QString & name) const;

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
    QString m_templateName;
    QList<QString> m_urls;
    QStringList m_subjectslist;
    QHash<QString, QString> m_templateNames;

public slots:
    void finishedSlot(QNetworkReply * reply);
    void finishedSubjectListSlot(QNetworkReply * reply);

};

#endif // DOWNLOADTEMPLATE_H
