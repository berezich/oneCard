#include "httpmanager.h"

HttpManager::HttpManager(QObject *parent) : QObject(parent)
{
    reqTimeout = 7000;
}

HttpManager::~HttpManager()
{

}

void HttpManager::startdownloadFile(QUrl httpUrl)
{
    url = httpUrl;

    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        emit fileErrDownload(REQFILE_SAVE_ERR,ServerEror::errToString(REQFILE_SAVE_ERR));
        delete file;
        file = 0;
        return;
    }

    // schedule the request
    httpRequestAborted = false;
    timer.start(reqTimeout,this);
    startRequest(url);

}

void HttpManager::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SIGNAL(updateDataReadProgress(qint64,qint64)));
}

void HttpManager::httpFinished()
{
    timer.stop();
    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
    int status = statusCode.toInt();
    qDebug() << "HttpManager::httpFinished: resp satus =" << status;
    if ( !statusCode.isValid() )
    {
        httpRequestAborted = true;
        qDebug()<<"HttpManager::httpFinished:  msg = "+reply->errorString();
        //emit fileErrDownload(TIMEOUT,tr("СЕРВЕР НЕ ДОСТУПЕН"));
        emit fileErrDownload(NO_CONNECTION,ServerEror::errToString(NO_CONNECTION));
    }
    if ( status != 200 )
    {
        httpRequestAborted = true;
        QString reason = reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();
        qDebug() <<"HttpManager::httpFinished:  msg =" << reason;
        emit fileErrDownload(WEB_SERVER_ERR,ServerEror::errToString(WEB_SERVER_ERR));
    }


    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        return;
    }

    file->flush();
    file->close();

    /*
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file->remove();
        emit fileErrDownload(11,reply->errorString());
    } else if (!redirectionTarget.isNull()) {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        url = newUrl;
        reply->deleteLater();
        file->open(QIODevice::WriteOnly);
        file->resize(0);
        startRequest(url);
        return;
    }
    */

    reply->deleteLater();
    reply = 0;
    emit fileDownloaded(file->fileName());
    delete file;
    file = 0;

}

void HttpManager::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());
}

void HttpManager::timerEvent(QTimerEvent *e)
{
    if(e->timerId()==timer.timerId())
    {
        qDebug() << "HttpManager:: timeout!";
        timer.stop();
        httpRequestAborted = true;
        emit fileErrDownload(TIMEOUT,ServerEror::errToString(TIMEOUT));
    }
    else
        timerEvent(e);
}

