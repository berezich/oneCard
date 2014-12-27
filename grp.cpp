#include "grp.h"


Grp::Grp(int id, QString name, QString imgSrc, QString imgPushSrc){
    _id = id;
    _name = name;
    _imgSrc = imgSrc;
    _imgPushSrc = imgPushSrc;
    cardsLst = new QList<CardInfo>();
}


void Grp::setId(int val){
    _id = val;
}

int Grp::getId(){
    return _id;
}

void Grp::setName(QString val){
    _name = val;
}

QString Grp::getName(){
    return _name;
}

void Grp::setImgSrc(QString val){
    _imgSrc = val;
}

QString Grp::getImgSrc(){
    return _imgSrc;
}

void Grp::setImgPushSrc(QString val){
    _imgPushSrc = val;
}

QString Grp::getImgPushSrc(){
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



