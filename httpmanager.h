#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QNetworkReply>

class HttpManager : public QObject
{
    Q_OBJECT
public:
    explicit HttpManager(QObject *parent = 0);
    ~HttpManager();

    void startdownloadFile(QUrl httpUrl);
    void cancelDownload(){httpRequestAborted=true;}

private slots:
    void startRequest(QUrl url);
    void httpFinished();
    void httpReadyRead();
signals:
    fileDownloaded(QFile *file);
    fileErrDownload(int errCode, QString errMsg);
    updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
private:
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    bool httpRequestAborted;
};

#endif // HTTPMANAGER_H
