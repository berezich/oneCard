#ifndef APPSTATE_H
#define APPSTATE_H


enum SCREEN_TYPE{LOCAL_GRP_SCREEN,CLOUD_LST_SCREEN,CARD_LST_SCREEN,CARD_INFO_SCREEN,GALLERY_SCREEN};
enum GRP_SOURCE{LOCAL, CLOUD};
enum CARD_SIDE{FRONTSIDE, BACKSIDE};
class AppState
{
private:
    GRP_SOURCE curGrpType;
    CARD_SIDE curSideCard;
    int curGrpId;
    int curCardId;
public:
    AppState();

    GRP_SOURCE getCurGrpType(){return curGrpType;}
    void setCurGrpType(GRP_SOURCE type){curGrpType=type;}

    int getCurGrpId(){return curGrpId;}
    void setCurGrpId(int grpId){curGrpId=grpId;}

    int getCurCardId(){return curCardId;}
    void setCurCardId(int cardId){curCardId=cardId;}

    CARD_SIDE getCurCardSideState(){return curSideCard;}
    void setCurCardSideState(CARD_SIDE st){curSideCard = st;}
};

#endif // APPSTATE_H