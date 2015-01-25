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


CardInfo::~CardInfo()
{

}

