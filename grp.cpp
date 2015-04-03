#include "grp.h"


Grp::Grp()
{
    _id = -99;
    _name = "";
    _imgSrc = "";
    _imgPushSrc = "";
    cardsLst = new QList<CardInfo>();
    _idSrv = -99;
}

Grp::Grp(int id, QString name, QString imgSrc, QString imgPushSrc, int idSrv){
    _id = id;
    _name = name;
    _imgSrc = imgSrc;
    _imgPushSrc = imgPushSrc;
    cardsLst = new QList<CardInfo>();
    _idSrv = idSrv;
}


void Grp::setId(int val){
    _id = val;
}

int Grp::getId()const{
    return _id;
}

void Grp::setName(QString val){
    _name = val;
}

QString Grp::getName()const{
    return _name;
}

void Grp::setImgSrc(QString val){
    _imgSrc = val;
}

QString Grp::getImgSrc()const{
    return _imgSrc;
}

void Grp::setImgPushSrc(QString val){
    _imgPushSrc = val;
}

QString Grp::getImgPushSrc()const{
    return _imgPushSrc;
}

CardInfo *Grp::createNewCard()
{
    addCard(CardInfo(_id*100+cardsLst->length()+1,_id,"НАЗВАНИЕ"));
    return &(cardsLst->last());
}

CardInfo *Grp::getCardInfo(int cardId)
{
    for(int i=0; i<cardsLst->length(); i++)
        if((*cardsLst)[i].getId()==cardId)
            return &(*cardsLst)[i];
    return new CardInfo();
}

void Grp::setCardLst(QList<CardInfo> *cards)
{
    cardsLst->clear();
    for(int i=0; i<cards->length(); i++)
        cardsLst->append((*cards)[i]);
}

QList<CardInfo *> *Grp::getCardsByIdSrv(int cardIdSrv)
{
    QList<CardInfo *> *cards = new QList<CardInfo*>();
    cards->clear();
    for(int i=0; i < cardsLst->length(); i++)
        if((*cardsLst)[i].idSrv()==cardIdSrv)
            cards->append(&((*cardsLst)[i]));

    return cards;
}

QDataStream& operator<<(QDataStream& out, const Grp& grp)
{
    out << grp.getId() << grp.getIdSrv() << grp.getName() << grp.getImgSrc() << *grp.getCards();
    return out;
}

QDataStream& operator>>(QDataStream& in, Grp& grp)
{
    int iVal;
    in >> iVal;
    grp.setId(iVal);
    in >> iVal;
    grp.setIdSrv(iVal);
    QString sVal;
    in >> sVal;
    grp.setName(sVal);
    in >> sVal;
    grp.setImgSrc(sVal);
    QList<CardInfo> cardLst;
    in >>cardLst;
    grp.setCardLst(&cardLst);
    return in;
}

