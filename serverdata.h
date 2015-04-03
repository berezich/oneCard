#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QObject>

class ServerData : public QObject
{
    Q_OBJECT
public:
    explicit ServerData(QObject *parent = 0);
    ~ServerData();

signals:

public slots:
};

#endif // SERVERDATA_H
