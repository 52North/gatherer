#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>

class Options : public QObject
{
    Q_OBJECT
public:
    explicit Options(QObject *parent = 0);

    QString server();
    void setServer(QString server);
    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)

    QString observer();
    void setObserver(QString observer);
    Q_PROPERTY(QString observer READ observer WRITE setObserver NOTIFY observerChanged)

    QString current();
    void setCurrent(QString current);
    Q_PROPERTY(QString current READ current WRITE setCurrent NOTIFY currentChanged)

    Q_INVOKABLE void save();

signals:
    void serverChanged();
    void observerChanged();
    void currentChanged();

public slots:

private:
    QString m_server;
    QString m_observer;
    QString m_current;
};

#endif // OPTIONS_H
