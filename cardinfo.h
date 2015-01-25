#ifndef CARDINFO_H
#define CARDINFO_H
#include <QString>
class CardInfo
{
public:
    CardInfo(int id=-1, int grpId=-1, QString cardName="", QString cardCom="", QString iSrc="",QString iBackSrc="", bool magnetLine=false, QString magnet="");
    ~CardInfo();
private:
    int id;
    int idSrv;
    int grpId;
    QString name;
    QString comment;
    QString imgSrc;
    QString imgBackSrc;
    bool isMagnetLine;
    QString magnet;

public:
    int getId(){return id;}
    int getGrpId(){return grpId;}
    QString getCardName(){return name;}
    QString getCardComment(){return comment;}
    QString getCardImgSrc(){return imgSrc;}
    QString getCardImgBackSrc(){return imgBackSrc;}
    bool getIsMagnetLine(){return isMagnetLine;}
    QString getMagnet(){return magnet;}

    void setCardName(QString txt){name=txt;}
    void setCardImgSrc(QString path){imgSrc = path;}
    void setCardImgBackSrc(QString path){imgBackSrc = path;}
    void setFlagMagnetLine(bool flag){isMagnetLine=flag;}
    void setMagnet(QString magnetLine){magnet = magnetLine;}

};

#endif // CARDINFO_H
