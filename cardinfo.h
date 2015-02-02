#ifndef CARDINFO_H
#define CARDINFO_H
#include <QString>
class CardInfo
{
public:
    CardInfo(int id, int grpId=-1, QString cardName="", QString cardCom="", QString iSrc="",QString iBackSrc="", bool magnetLine=false, QString magnet="");
    CardInfo(int id=-1, int idSrv = -1, int grpId=-1, int grpIdSrv = -1, QString cardName="", QString cardCom="", bool isImgLocal=true,QString iSrc="",QString iBackSrc="", bool magnetLine=false, QString magnet="");
    ~CardInfo();
private:
    int id;
    int _idSrv;
    int grpId;
    int _idGrpSrv;
    QString name;
    QString comment;
    QString imgSrc;
    QString imgBackSrc;
    bool _isImgLocal;
    bool isMagnetLine;
    QString magnet;

public:
    int getId(){return id;}
    int idSrv(){return _idSrv;}
    int idGrpSrv(){return _idGrpSrv;}
    int getGrpId(){return grpId;}
    QString getCardName(){return name;}
    QString getCardComment(){return comment;}
    QString getCardImgSrc(){return imgSrc;}
    QString getCardImgBackSrc(){return imgBackSrc;}
    bool getIsMagnetLine(){return isMagnetLine;}
    QString getMagnet(){return magnet;}
    bool isImgLocal(){return _isImgLocal;}

    void setCardId(int id){this->id = id;}
    void setCardGrpId(int id){grpId = id;}
    void setCardIdSrv(int id){_idSrv = id;}
    void setCardIdGrpSrv(int id){_idGrpSrv = id;}
    void setCardName(QString txt){name=txt;}
    void setCardImgSrc(QString path){imgSrc = path;}
    void setCardImgBackSrc(QString path){imgBackSrc = path;}
    void setFlagMagnetLine(bool flag){isMagnetLine=flag;}
    void setMagnet(QString magnetLine){magnet = magnetLine;}
    void setIsImgLocal(bool val){_isImgLocal = val;}

};

#endif // CARDINFO_H
