#ifndef CARDINFO_H
#define CARDINFO_H
#include <QString>
class CardInfo
{
public:
    CardInfo(int id, int grpId, QString cardName, QString cardCom, QString iSrc);
    ~CardInfo();
private:
    int id;
    int grpId;
    QString name;
    QString comment;
    QString imgSrc;

public:
    int getId(){return id;}
    int getGrpId(){return grpId;}
    QString getCardName(){return name;}
    QString getCardComment(){return comment;}
    QString getCardImgSrc(){return imgSrc;}
};

#endif // CARDINFO_H
