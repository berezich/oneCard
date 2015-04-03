#ifndef CARDINFO_H
#define CARDINFO_H
#include <QString>
#include <QDataStream>
class CardInfo
{
public:
    CardInfo(int id, int grpId=-1, QString cardName="", QString iSrc="", QString iBackSrc="", bool magnetLine=true, QString magnet="");
    CardInfo(int id=-1, int idSrv = -1, int grpId=-1, int grpIdSrv = -1, QString cardName="", QString cardCom="", bool isImgLocal=true,QString iSrc="",QString iBackSrc="", bool magnetLine=false, QString magnet="");
    ~CardInfo();
private:
    int id;
    int _idSrv;
    int grpId;
    int _idGrpSrv;
    QString name;
    QString imgSrc;
    QString imgBackSrc;
    bool _isImgLocal;
    bool isMagnetLine;
    QString magnet;

public:
    int getId()const{return id;}
    int idSrv()const{return _idSrv;}
    int idGrpSrv()const{return _idGrpSrv;}
    int getGrpId()const{return grpId;}
    QString getCardName()const{return name;}
    QString getCardImgSrc()const{return imgSrc;}
    QString getCardImgBackSrc()const{return imgBackSrc;}
    bool getIsMagnetLine()const{return isMagnetLine;}
    QString getMagnet()const{return magnet;}
    bool isImgLocal()const{return _isImgLocal;}

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
    void setCardInfo(CardInfo *card);
    bool cmpCardData(CardInfo *card);

};
QDataStream& operator<<(QDataStream& out, const CardInfo& card);
QDataStream& operator>>(QDataStream& in, CardInfo& card);

#endif // CARDINFO_H
