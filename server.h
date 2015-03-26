#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>
#include <QXmlStreamReader>
#include "grp.h"
#include "httpmanager.h"
#include "servererrors.h"
class Server: public QObject
{
    Q_OBJECT
private: enum REQ_TYPE{GET_GRPS, GET_CARDS, GET_CARD_DATA};
public:
    explicit Server(QObject *parent = 0);
    ~Server();
    void setLgnPwd(QString login, QString pass){ this->login = login; this->pass= pass;}
    void setEndPoint(QString ip, int port=-1, QString path="");
    void getGrpLstStart();
    void getCardLstStart(int idGrpSrv);
    void downloadCardDataStart(int idCardSrv,int idGrpSrv);
    void cancelDownloading(){httpManager->cancelDownload();}
    QList <Grp> *getGrpLastLst(){return grpLstTmp;}
    Grp *getGrpTmp(int grpIdSrv);
    CardInfo *getCardTmp(int grpIdSrv, int cardIdSrv);
    bool isGrpLstDownloaded(){return _isGrpLstDownloaded;}
signals:
    void getGrpLstFinish(SERVER_ERRORS errCode, QString errMsg);
    void getCardLstFinish(SERVER_ERRORS errCode, QString errMsg);
    void downloadCardDataFinish(SERVER_ERRORS errCode, QString errMsg);

private slots:
    void onGrpLstDownloaded(QString fileName);
    void onCardLstDownloaded(QString fileName);
    void onCardDataDownloaded(QString fileName);
    void onProcReqError(SERVER_ERRORS errCode, QString errMsg);
private:
    REQ_TYPE reqType;
    QString login;
    QString pass;
    QString endPoint;
    int idGrp;
    int idCard;
    CardInfo *curCard;
    Grp *curGrp;
    bool isFImgDownLoaded;
    bool isBImgDownLoaded;
    void getImgStart(QString imgSrvName);

    QList<Grp> *grpLstTmp;
    bool _isGrpLstDownloaded;


    HttpManager *httpManager;
    HttpManager *httpManager1;
    void init()
    {
        httpManager = NULL;
        httpManager1 = NULL;
        _isGrpLstDownloaded = false;
    }
};

#endif // SERVER_H
