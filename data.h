#ifndef DATA_H
#define DATA_H
#include "grp.h"
#include "cardinfo.h"

class Data
{
public:
    Data();
    ~Data();

    QList<Grp> getLocalGroups();
    QList<CardInfo> *getLocalCards(int grpId);
    Grp *getLocalGrp(int grpId);
    CardInfo *getLocalCard(int grpId, int cardId);
private:

    QList<Grp> localGrpLst;

};

#endif // DATA_H
