#ifndef APPSTATE_H
#define APPSTATE_H


enum SCREEN_TYPE{LOCAL_GRP_SCREEN,CLOUD_LST_SCREEN,CARD_LST_SCREEN,CARD_INFO_SCREEN};
enum GRP_SOURCE{LOCAL, CLOUD};
class AppState
{
private:
    GRP_SOURCE curGrpType;
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
};

#endif // APPSTATE_H
