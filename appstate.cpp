#include "appstate.h"

AppState::AppState()
{
    init();
}

void AppState::setTmpCardInfo(CardInfo *tmpCardInfo)
{
//    _tmpCardInfo.setCardId(tmpCardInfo->getId());
//    _tmpCardInfo.setCardIdSrv(tmpCardInfo->idSrv());
//    _tmpCardInfo.setCardGrpId(tmpCardInfo->getGrpId());
//    _tmpCardInfo.setCardIdGrpSrv(tmpCardInfo->idGrpSrv());
//    _tmpCardInfo.setCardName(tmpCardInfo->getCardName());
//    _tmpCardInfo.setCardImgSrc(tmpCardInfo->getCardImgSrc());
//    _tmpCardInfo.setCardImgBackSrc(tmpCardInfo->getCardImgBackSrc());
//    _tmpCardInfo.setIsImgLocal(tmpCardInfo->isImgLocal());
//    _tmpCardInfo.setFlagMagnetLine(tmpCardInfo->getIsMagnetLine());
//    _tmpCardInfo.setMagnet(tmpCardInfo->getMagnet());

    _tmpCardInfo.setCardInfo(tmpCardInfo);

    _tmpCardInfo.setCardId(tmpCardInfo->getId());
    _tmpCardInfo.setCardGrpId(tmpCardInfo->getGrpId());

}


