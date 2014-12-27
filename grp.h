#ifndef GRP_H
#define GRP_H
#include <QString>
#include <QObject>
#include <QList>
#include "cardinfo.h"

class Grp
{
//    Q_OBJECT
//    Q_PROPERTY(QString _id READ getId WRITE setId)
//    Q_PROPERTY(QString _name READ getName WRITE setName)
//    Q_PROPERTY(QString _imgSrc READ getImgSrc WRITE setImgSrc)
//    Q_PROPERTY(QString _imgPushSrc READ getImgPushSrc WRITE setImgPushSrc)
private:
    int _id;
    QString _name;
    QString _imgSrc;
    QString _imgPushSrc;
protected:

public:
    QList<CardInfo> *cardsLst;
    Grp();
    Grp(int id, QString name, QString imgSrc, QString imgPushSrc);

    void setId(int val);

    int getId();

    void setName(QString val);

    QString getName();

    void setImgSrc(QString val);

    QString getImgSrc();

    void setImgPushSrc(QString val);

    QString getImgPushSrc();

    void addCard(CardInfo card){cardsLst->append(card);}
    CardInfo *createNewCard();
    void delCard(int iCard){cardsLst->removeAt(iCard);}
    QList<CardInfo> *getCards(){return cardsLst;}
    CardInfo *getCardInfo(int cardId);
    void clearCards(){cardsLst->clear();}
};

#endif // GRP_H
