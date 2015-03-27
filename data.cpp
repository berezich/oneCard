#include "data.h"

Data::Data()
{
    init();
    int i=1;
    //default groups and cards
    localGrpLst.clear();
    Grp gr1(i++, "Транспорт", "car.svg", "");
    Grp gr2 (i++,"Спорт", "fit.svg", "");
    Grp gr3 (i++,"Рестораны", "food.svg", "");
    Grp gr4 (i++,"Аптеки", "med.svg", "");
    Grp gr5 (i++,"Туризм", "plane.svg", "");
    Grp gr6 (i++,"Ремонт", "rebild.svg", "");
    Grp gr7 (i++,"Магазины", "shop.svg", "");
    Grp gr8 (i++,"Солярий", "sun.svg", "");
    Grp gr9 (i++,"Разное", "different.svg", "");

    localGrpLst.append(gr1);
    localGrpLst.append(gr2);
    localGrpLst.append(gr3);
    localGrpLst.append(gr4);
    localGrpLst.append(gr5);
    localGrpLst.append(gr6);
    localGrpLst.append(gr7);
    localGrpLst.append(gr8);
    localGrpLst.append(gr9);

    int k;
    for(i=0; i<localGrpLst.length(); i++)
    {
        k=(i+1)*100;
        if(i==0)
            for(int j=0; j<1; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"АВТОТЕРРИТОРИЯ",":/cardsImg/auto.png"));
        if(i==1)
            for(int j=0; j<2; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"NICE FITNESS",":/cardsImg/fitnes.png"));
        if(i==2)
            for(int j=0; j<3; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"НИХОН",":/cardsImg/food.png"));
        if(i==4)
            for(int j=0; j<4; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"ЧИП ТРИП",":/cardsImg/travel.png"));
        if(i==6)
            for(int j=0; j<1; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"АШАН",":/cardsImg/ashan.png"));
        if(i==7)
            for(int j=0; j<1; j++)
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"САН-СИТИ",":/cardsImg/sun.png"));
        if(i==8)
            for(int j=0; j<1; j++)
            {
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"ЖЕНСКАЯ ОДЕЖДА",":/cardsImg/other.png"));
                localGrpLst[i].addCard( CardInfo(k++,localGrpLst[i].getId(),"ЛЕТУАЛЬ",":/cardsImg/letual.png"));
            }

    }

    //list of grp icon resources

    grpImgSrcLst.append("car.svg");
    grpImgSrcLst.append("fit.svg");
    grpImgSrcLst.append("food.svg");
    grpImgSrcLst.append("med.svg");
    grpImgSrcLst.append("plane.svg");
    grpImgSrcLst.append("rebild.svg");
    grpImgSrcLst.append("shop.svg");
    grpImgSrcLst.append("sun.svg");
    grpImgSrcLst.append("different.svg");
    grpImgSrcLst.append("star.svg");
}

Data::~Data()
{

}

QList<Grp> Data::getLocalGroups()const
{
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

CardInfo *Data::getLocalCard(int grpId, int cardId)
{
    CardInfo *card;
    for(int i=0; i<localGrpLst.length(); i++)
        if(localGrpLst[i].getId()==grpId)
            for(int k=0; k<localGrpLst[i].cardsLst->length(); k++)
            {
                card = localGrpLst[i].getCardInfo(cardId);
                return card;
            }
    return NULL;
}

void Data::saveImg(QString fromSrc, QString toSrc, QSize imgSaveSize, bool replace)
{

    if(replace || !QFile::exists(toSrc))
    {
        QFile file(toSrc);
        if(file.open(QIODevice::WriteOnly))
        {

            QImage *picImg = new QImage(fromSrc);
            if(picImg->height()>picImg->width())
            {
                QTransform trans;
                QImage *picImgRotate = new QImage( picImg->transformed(trans.rotate(-90)));
                delete(picImg);
                picImg = picImgRotate;
            }
            QPixmap::fromImage(picImg->scaled(imgSaveSize,Qt::KeepAspectRatio)).save(&file, "jpeg");
            delete(picImg);
            file.close();

        }
    }
}

void Data::cacheLastImg(QString cacheFromDir, QString cacheToDir, int num, QSize imgSaveSize )
{
    QStringList photoLst;

    QDir dir(cacheToDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QDir srcDir = QDir( cacheFromDir );
    srcDir.setSorting(QDir::Time);
    QStringList filters;
    filters << "*.jpg";
    srcDir.setNameFilters(filters);
    photoLst = srcDir.entryList();

    QString filePath="";
    if(photoLst.length()>0)
        filePath = srcDir.absoluteFilePath(photoLst.at(0));

    for(int i= (photoLst.length()>=num)? num-1 : photoLst.length()-1; i>=0 ; i--)
        saveImg(cacheFromDir+photoLst[i],cacheToDir+photoLst[i],imgSaveSize,false);
}

QStringList Data::getGrpImgSrc()
{
    return grpImgSrcLst;
}
void Data::addNewGrp(QString name, QString grpImgSrc)
{

    Grp gr1(localGrpLst.length()+1, name, grpImgSrc, "");
    localGrpLst.append(gr1);
}

void Data::setGrpLst(QList<Grp> *grpLst, DATA_SOURCE src)
{
    switch (src) {
    case LOCAL:
        localGrpLst.clear();
        for(int i=0; i<grpLst->length(); i++)
            localGrpLst.append((*grpLst)[i]);
        grpLst->clear();
        break;
    default:
        break;
    }
}

void Data::setCardInfo(int grpId, int cardId, CardInfo *card)
{
    CardInfo *cardInfo;
    if((cardInfo = getLocalCard(grpId,cardId))!= NULL)
        cardInfo->setCardInfo(card);
}

Grp *Data::findLocalGrp(QString grpName, QString grpIcon)
{
    for(int i=0; i<localGrpLst.length(); i++)
        if(localGrpLst[i].getName() == grpName && localGrpLst[i].getImgSrc()==grpIcon)
            return &localGrpLst[i];
    return NULL;
}

void Data::saveCardFromSrv(Grp *grp, CardInfo *card, QString toSrcDir, QSize imgSaveSize)
{
    CardInfo *cardInf;
    QString name;
    Grp *grp1;
    if(grp!=NULL && card!=NULL)
    {
        if((grp1 = findLocalGrp(grp->getName(),grp->getImgSrc()))==NULL)
        {
            addNewGrp(grp->getName(),grp->getImgSrc());
            grp1 = findLocalGrp(grp->getName(),grp->getImgSrc());
        }
        if(grp1!=NULL)
        {
            QList<CardInfo *> *cards;
            if((cards = grp1->getCardsByIdSrv(card->idSrv()))!=NULL)
            {
                for(int i=0; i<cards->length(); i++)
                    if(cards->at(i)->cmpCardData(card))
                        return;
            }
            if((cardInf = grp1->createNewCard())!=NULL)
            {
                cardInf->setCardInfo(card);
                if((name = card->getCardImgSrc())!="")
                    saveImg(name,toSrcDir+"/"+QString::number(cardInf->getGrpId())+"_"+QString::number(cardInf->getId())+"_"+name,imgSaveSize);
                if((name = card->getCardImgBackSrc())!="")
                    saveImg(name,toSrcDir+"/"+QString::number(cardInf->getGrpId())+"_"+QString::number(cardInf->getId())+"_"+name,imgSaveSize);
            }
        }
    }
}
QDataStream& operator<<(QDataStream& out, const Data& data)
{
    out << data.getLocalGroups();
    return out;
}

QDataStream& operator>>(QDataStream& in, Data& data)
{
    QList<Grp> *grpLst = new QList<Grp>();
    in >> *grpLst;
    data.setGrpLst(grpLst,LOCAL);
    return in;
}
