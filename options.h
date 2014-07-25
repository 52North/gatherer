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
    Q_PROPERTY(QString server READ server WRITE setServer)

    QString observer();
    void setObserver(QString observer);
    Q_PROPERTY(QString observer READ observer WRITE setObserver)

    Q_INVOKABLE void save();

signals:

public slots:

private:
    QString m_server;
    QString m_observer;
};

#endif // OPTIONS_H
