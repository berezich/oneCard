#ifndef GRP_H
#define GRP_H
#include <QString>
#include <QObject>
#include <QList>
#include <QDataStream>
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
    int _idSrv;
    QString _name;
    QString _imgSrc;
    QString _imgPushSrc;
protected:

public:
    QList<CardInfo> *cardsLst;
    Grp();
    Grp(int id, QString name, QString imgSrc, QString imgPushSrc, int idSrv=-1);
    // if idSrv == -1 this is no the group on server

    void setId(int val);

    int getId()const;

    void setIdSrv(int val){_idSrv = val;}

    int getIdSrv()const{return _idSrv;}

    void setName(QString val);

    QString getName()const;

    void setImgSrc(QString val);

    QString getImgSrc()const;

    void setImgPushSrc(QString val);

    QString getImgPushSrc()const;


    void addCard(CardInfo card){cardsLst->append(card);}
    CardInfo *createNewCard();
    void delCard(int iCard){cardsLst->removeAt(iCard);}
    QList<CardInfo> *getCards()const{return cardsLst;}
    CardInfo *getCardInfo(int cardId);
    void clearCards(){cardsLst->clear();}
    void setCardLst(QList<CardInfo> *cards);
};
QDataStream& operator<<(QDataStream& out, const Grp& grp);
QDataStream& operator>>(QDataStream& in, Grp& grp);

#endif // GRP_H
