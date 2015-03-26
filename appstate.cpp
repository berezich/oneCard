#include "appstate.h"

AppState::AppState()
{
    init();
}

void AppState::setTmpCardInfo(CardInfo *tmpCardInfo)
{
    _tmpCardInfo.setCardInfo(tmpCardInfo);
    _tmpCardInfo.setCardId(tmpCardInfo->getId());
    _tmpCardInfo.setCardGrpId(tmpCardInfo->getGrpId());

}


