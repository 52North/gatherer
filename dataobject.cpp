// Author: B.P. Ottow
// Date: August 2014
// GSoC Project: Gatherer, ILWIS Mobile. Hosted by 52 North and ITC Enschede.
//
// This is the source file for the class DataObject which stores data for list models.

#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
{
}

/// Constructor for the lists of templates
DataObject::DataObject(const QString &name, const QString &url, QObject *parent)
    : QObject(parent), m_name(name), m_url(url)
{
}

/// Constructor for the list of observations
DataObject::DataObject(const QString &time, const QString &subjectname, const QString &data, QObject *parent)
    : QObject(parent), m_time(time), m_subjectname(subjectname), m_data(data)
{

}

QString DataObject::name() const
{
    return m_name;
}

void DataObject::setName(const QString &name)
{
    m_name = name;
}

QString DataObject::url() const
{
    return m_url;
}

void DataObject::setUrl(const QString &url)
{
    m_url = url;
}

QString DataObject::time() const
{
    return m_time;
}

QString DataObject::subjectname() const
{
    return m_subjectname;
}

QString DataObject::data() const
{
    return m_data;
}

