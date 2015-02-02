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

