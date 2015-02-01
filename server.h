#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>
#include <QXmlStreamReader>
#include "grp.h"
//#include "cardinfo.h"
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
    void downloadCardDataStart(int idCadSrv,int idGrp, int idCard, QString fImgSrvName, QString bImgSrvName, QString localPathForImg);
    void cancelDownloading(){httpManager.cancelDownload();}
    QList <Grp> *getGrpLastLst(){return grpLstTmp;}
    Grp *getGrpTmp(int grpIdSrv);
    bool isGrpLstDownloaded(){return _isGrpLstDownloaded;}
signals:
    void getGrpLstFinish(SERVER_ERRORS errCode, QString errMsg);
    //getGrpLstFinish();
    void getCardLstFinish(SERVER_ERRORS errCode, QString errMsg);
    void downloadCardDataFinish(int idGrp, int idCard, QString fImgSrvName, QString bImgSrvName, int errCode, QString errMsg);

private slots:
    void onGrpLstDownloaded(QString fileName);
    void onCardLstDownloaded(QString fileName);
//    void onCardDataDownloaded(QFile *fileResponse);
//    void onFImgDownloaded(QFile *fileImg);
//    void onBImgDownLoaded(QFile *fileImg);
    void onProcReqError(SERVER_ERRORS errCode, QString errMsg);
private:
    REQ_TYPE reqType;
    QString login;
    QString pass;
    QString endPoint;
    int idGrp;
    int idCard;
    QString fImgLocName;
    QString bImgLocName;
    //bool isFImgDownLoaded;
    //bool isBImgDownLoaded;
    void getImgStart(QString imgSrvName);

    QList<Grp> *grpLstTmp;
    bool _isGrpLstDownloaded;


    HttpManager httpManager;
    void init()
    {
        _isGrpLstDownloaded = false;
    }
};

#endif // SERVER_H
