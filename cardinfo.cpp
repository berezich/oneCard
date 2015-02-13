#include "cardinfo.h"


CardInfo::CardInfo(int id, int grpId, QString cardName, QString cardCom, QString iSrc,QString iBackSrc, bool magnetLine, QString magnet)
{
    this->id = id;
    this->grpId = grpId;
    name = cardName;
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
    imgSrc = iSrc;
    imgBackSrc = iBackSrc;
    isMagnetLine = magnetLine;
    this->magnet = magnet;
    this->_isImgLocal = isImgLocal;
}


CardInfo::~CardInfo()
{

}

void CardInfo::setCardInfo(CardInfo *card)
{
    _idSrv = card->idSrv();
    _idGrpSrv = card->idGrpSrv();
    name = card->getCardName();
    imgSrc = card->getCardImgSrc();
    imgBackSrc = card->getCardImgBackSrc();
    _isImgLocal = card->isImgLocal();
    isMagnetLine = card->getIsMagnetLine();
    magnet = card->getMagnet();

}

bool CardInfo::cmpCardData(CardInfo *card)
{
    if(name == card->getCardName())
        if(imgSrc.indexOf(card->getCardImgSrc())>=0)
            if(imgBackSrc.indexOf(card->getCardImgBackSrc())>=0)
                if(_isImgLocal == card->isImgLocal())
                    if(isMagnetLine == card->getIsMagnetLine())
                        if(magnet == card->getMagnet())
                            return true;
    return false;
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
