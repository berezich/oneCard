#include "cardinfo.h"


CardInfo::CardInfo(int id, int grpId, QString cardName, QString cardCom, QString iSrc)
{
    this->id = id;
    this->grpId = grpId;
    name = cardName;
    comment = cardCom;
    imgSrc = iSrc;
}

CardInfo::~CardInfo()
{

}

