#include "data.h"

Data::Data()
{

}

Data::~Data()
{

}

QList<Grp> Data::getLocalGroups()
{
    //получение списка групп из файловой системы

    int i=1;
    localGrpLst.clear();
    Grp gr1(i++, "Транспорт", ":/svg/grpIcons/car.svg", ":/svg/grpIcons/carPUSH.svg");
    Grp gr2 (i++,"Спорт", ":/svg/grpIcons/fit.svg", ":/svg/grpIcons/fitPUSH.svg");
    Grp gr3 (i++,"Рестораны", ":/svg/grpIcons/food.svg", ":/svg/grpIcons/foodPUSH.svg");
    Grp gr4 (i++,"Аптеки", ":/svg/grpIcons/med.svg", ":/svg/grpIcons/medPUSH.svg");
    Grp gr5 (i++,"Туризм", ":/svg/grpIcons/plane.svg", ":/svg/grpIcons/planePUSH.svg");
    Grp gr6 (i++,"Ремонт", ":/svg/grpIcons/rebild.svg", ":/svg/grpIcons/rebildPUSH.svg");
    Grp gr7 (i++,"Магазины", ":/svg/grpIcons/shop.svg", ":/svg/grpIcons/shopPUSH.svg");
    Grp gr8 (i++,"Солярий", ":/svg/grpIcons/sun.svg", ":/svg/grpIcons/sunPUSH.svg");
    Grp gr9 (i++,"Разное", ":/svg/grpIcons/different.svg", ":/svg/grpIcons/differentPUSH.svg");
    Grp gr10 (i++, "", ":/svg/grpIcons/new.svg", ":/svg/grpIcons/newPUSH.svg");

    localGrpLst.append(gr1);
    localGrpLst.append(gr2);
    localGrpLst.append(gr3);
    localGrpLst.append(gr4);
    localGrpLst.append(gr5);
    localGrpLst.append(gr6);
    localGrpLst.append(gr7);
    localGrpLst.append(gr8);
    localGrpLst.append(gr9);
    localGrpLst.append(gr10);

    int k;
    for(i=0; i<localGrpLst.length(); i++)
    {
        k=(i+1)*100;
        if(i==0)
            for(int j=0; j<1; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"АВТОТЕРРИТОРИЯ","КАРТА СКИДКА 5%",":/cardsImg/auto.png"));
        if(i==1)
            for(int j=0; j<2; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"NICE FITNESS","КЛУБНАЯ КАРТА",":/cardsImg/fitnes.png"));
        if(i==2)
            for(int j=0; j<3; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"НИХОН","КАРТА ПОСТЯННОГО КЛИЕНТА",":/cardsImg/food.png"));
//        if(i==3)
//            for(int j=0; j<3; j++)
//                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"АВТОТЕРРИТОРИЯ","КАРТА СКИДКА 5%",":/cardsImg/auto.png"));
        if(i==4)
            for(int j=0; j<4; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"ЧИП ТРИП","КАРТА СКИДКА 3%",":/cardsImg/travel.png"));
//        if(i==5)
//            for(int j=0; j<3; j++)
//                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"АВТОТЕРРИТОРИЯ","КАРТА СКИДКА 5%",":/cardsImg/auto.png"));
        if(i==6)
            for(int j=0; j<1; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"АШАН","КАРТА СКИДКА 5%",":/cardsImg/ashan.png"));
        if(i==7)
            for(int j=0; j<1; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"САН-СИТИ","КАРТА НАКОПИТЕЛЬНАЯ",":/cardsImg/sun.png"));
        if(i==8)
            for(int j=0; j<1; j++)
            {
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"ЖЕНСКАЯ ОДЕЖДА","АКЦИЯ 50%",":/cardsImg/other.png"));
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"ЛЕТУАЛЬ","НАКОПИТЕЛЬНАЯ КАРТА",":/cardsImg/letual.png"));
            }

    }
    return localGrpLst;
}

QList<CardInfo> *Data::getLocalCards(int grpId)
{
    for(int i=0; i<localGrpLst.length(); i++)
        if(localGrpLst[i].getId()==grpId)
            return localGrpLst[i].cardsLst;
    return new QList<CardInfo>();
}

Grp *Data::getLocalGrp(int grpId)
{
    for(int i=0; i<localGrpLst.length(); i++)
        if(localGrpLst[i].getId()==grpId)
            return &(localGrpLst[i]);
}

