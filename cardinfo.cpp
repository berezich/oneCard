#include "cardinfo.h"


CardInfo::CardInfo(int id, int grpId, QString cardName, QString cardCom, QString iSrc,QString iBackSrc, bool magnetLine, QString magnet)
{
    this->id = id;
    this->grpId = grpId;
    name = cardName;
    comment = cardCom;
    imgSrc = iSrc;
    imgBackSrc = iBackSrc;
    isMagnetLine = magnetLine;
    this->magnet = magnet;
    this->_idGrpSrv = -99;
}

CardInfo::CardInfo(int id, int idSrv, int grpId, int grpIdSrv, QString cardName, QString cardCom, bool isImgLocal,QString iSrc, QString iBackSrc, bool magnetLine, QString magnet)
{
    this->id = id;
    this->_idSrv = idSrv;
    this->grpId = grpId;
    this->_idGrpSrv = grpIdSrv;
    name = cardName;
    comment = cardCom;
    imgSrc = iSrc;
    imgBackSrc = iBackSrc;
    isMagnetLine = magnetLine;
    this->magnet = magnet;
    this->_isImgLocal = isImgLocal;
}


CardInfo::~CardInfo()
{

}

QDataStream& operator<<(QDataStream& out, const CardInfo& card)
{
    out << card.getId() << card.idSrv() << card.getGrpId() << card.idGrpSrv() << card.getCardName() << card.getCardImgSrc() << card.getCardImgBackSrc() << card.getIsMagnetLine() << card.getMagnet() << card.isImgLocal();
    return out;
}

QDataStream& operator>>(QDataStream& in, CardInfo& card)
{
    int iVal;
    in >> iVal;
    card.setCardId(iVal);
    in >> iVal;
    card.setCardIdSrv(iVal);
    in >> iVal;
    card.setCardGrpId(iVal);
    in >> iVal;
    card.setCardIdGrpSrv(iVal);
    QString sVal;
    in >> sVal;
    card.setCardName(sVal);
    in >> sVal;
    card.setCardImgSrc(sVal);
    in >> sVal;
    card.setCardImgBackSrc(sVal);
    bool bVal;
    in >> bVal;
    card.setFlagMagnetLine(bVal);
    in >> sVal;
    card.setMagnet(sVal);
    in >> bVal;
    card.setIsImgLocal(bVal);

    return in;
}
