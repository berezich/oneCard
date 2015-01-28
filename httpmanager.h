#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QNetworkReply>
#include <QBasicTimer>
#include <QTimerEvent>
#include "servererrors.h"

class HttpManager : public QObject
{
    Q_OBJECT
public:
    explicit HttpManager(QObject *parent = 0);
    ~HttpManager();

    void startdownloadFile(QUrl httpUrl);
    void cancelDownload(){httpRequestAborted=true;}
    void setReqTimeout(int reqTimeout){this->reqTimeout = reqTimeout;}

private slots:
    void startRequest(QUrl url);
    void httpFinished();
    void httpReadyRead();
signals:
    void fileDownloaded(QString fileName);
    void fileErrDownload(SERVER_ERRORS errCode, QString errMsg);
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
private:
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    bool httpRequestAborted;
    QBasicTimer timer;
    int reqTimeout;
    void timerEvent (QTimerEvent *);
};

#endif // HTTPMANAGER_H
