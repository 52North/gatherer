// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This is the header file for the class DataObject which stores data for list models.

#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString time READ time CONSTANT)
    Q_PROPERTY(QString subjectname READ subjectname CONSTANT)
    Q_PROPERTY(QString data READ data CONSTANT)

public:
    DataObject(QObject *parent=0);
    DataObject(const QString &name, const QString &url, QObject *parent=0);
    DataObject(const QString &time, const QString &subjectname, const QString &data, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString url() const;
    void setUrl(const QString &url);

    QString time() const;

    QString subjectname() const;

    QString data() const;

signals:
    void nameChanged();
    void urlChanged();

private:
    QString m_name;
    QString m_url;
    QString m_time;
    QString m_subjectname;
    QString m_data;
};


#endif
