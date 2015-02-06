#ifndef APPSTATE_H
#define APPSTATE_H
#include "interface.h"
#include "datalocationtype.h"

enum SCREEN_TYPE{MAIN_CHOICE_SCREEN, GRP_SCREEN,CARD_LST_SCREEN,CARD_INFO_SCREEN,GALLERY_SCREEN, CAMERAQML_SCREEN, NEW_GRP_SCREEN};
enum CARD_SIDE{FRONTSIDE, BACKSIDE};
enum OS{NONE, WINDOWS, Android, IOS};
class AppState
{
private:
    DATA_SOURCE curGrpType;
    CARD_SIDE curSideCard;
    int curGrpId;
    int curCardId;
    SCREEN_TYPE curScreen;
    OS curOS;
    bool isFixedWinSize;

    //settings
public:
    AppState();

    DATA_SOURCE getCurGrpType(){return curGrpType;}
    void setCurGrpType(DATA_SOURCE type){curGrpType=type;}

    int getCurGrpId(){return curGrpId;}
    void setCurGrpId(int grpId){curGrpId=grpId;}

    int getCurCardId(){return curCardId;}
    void setCurCardId(int cardId){curCardId=cardId;}

    CARD_SIDE getCurCardSideState(){return curSideCard;}
    void setCurCardSideState(CARD_SIDE st){curSideCard = st;}

    SCREEN_TYPE getCurScreen(){return curScreen;}
    void setCurScreen(SCREEN_TYPE screen){curScreen=screen;}

    OS getCurOS(){return curOS;}
    void setCurOS(OS os){curOS = os;}

    bool getIsFixedWinSize(){return isFixedWinSize;}
    void setIsFixedWinSize(bool val){isFixedWinSize = val;}


private:
    void init()
    {
        isFixedWinSize=false;
    }
};

#endif // APPSTATE_H
