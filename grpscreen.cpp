#include "grpscreen.h"

GrpScreen::GrpScreen(QScreen *screenInfo, QWidget *parent):BlankScreen(screenInfo,parent)
{
    iconHeight = iconHeight*scaleFactor;
    iconWidth = iconWidth*scaleFactor;
    iconSize = iconSize*scaleFactor;
    textSize = textSize*qSqrt(scaleFactor);

    gridLayout = new QGridLayout(this);
    blankSpace->setLayout(gridLayout);




//    int i=0;
//    Grp gr1(i++, tr("Транспорт"), ":/svg/car.svg", ":/svg/carPUSH.svg");
//    Grp gr2 (i++,tr("Спорт"), ":/svg/fit.svg", ":/svg/fitPUSH.svg");
//    Grp gr3 (i++, tr("Рестораны"), ":/svg/food.svg", ":/svg/foodPUSH.svg");
//    Grp gr4 (i++, tr("Аптеки"), ":/svg/med.svg", ":/svg/medPUSH.svg");
//    Grp gr5 (i++, tr("Туризм"), ":/svg/plane.svg", ":/svg/planePUSH.svg");
//    Grp gr6 (i++, tr("Ремонт"), ":/svg/rebild.svg", ":/svg/rebildPUSH.svg");
//    Grp gr7 (i++, tr("Магазины"), ":/svg/shop.svg", ":/svg/shopPUSH.svg");
//    Grp gr8 (i++, tr("Солярий"), ":/svg/sun.svg", ":/svg/sunPUSH.svg");
//    Grp gr9 (i++, tr("Разное"), ":/svg/different.svg", ":/svg/differentPUSH.svg");
//    Grp gr10 (i++, tr(""), ":/svg/new.svg", ":/svg/newPUSH.svg");
//    QList <Grp> gr;
//    gr.append(gr1);
//    gr.append(gr2);
//    gr.append(gr3);
//    gr.append(gr4);
//    gr.append(gr5);
//    gr.append(gr6);
//    gr.append(gr7);
//    gr.append(gr8);
//    gr.append(gr9);
//    gr.append(gr10);


//    qDebug()<<"scaleFactor = "<<scaleFactor;
//    Icon *icon;
//    for(int i=0; i<10; i++)
//    {
//        if(i<11)
//            icon = new Icon(gr[i].getId(),gr[i].getName(),15*qSqrt(scaleFactor), gr[i].getImgSrc(), gr[i].getImgPushSrc(), *new QSize(190*scaleFactor,190*scaleFactor),*new QSize(230*scaleFactor,210*scaleFactor));
//        else
//            icon = new Icon();
//        gridLayout->addWidget(icon, qFloor(i/3),i%3);

//    }
    blankLayout->addStretch();
}

GrpScreen::~GrpScreen()
{

}

void GrpScreen::setGrpLst(QList<Grp> grpLst)
{
    Icon *icon;
    for(int i=0; i<columnsNum*rowsNum; i++)
    {
        if(i < grpLst.length())
        {
            icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpLst[i].getImgSrc(), grpLst[i].getImgPushSrc(), QSize(190*scaleFactor,190*scaleFactor)/*,*new QSize(230*scaleFactor,210*scaleFactor)*/);
            gridLayout->addWidget(icon, qFloor(i/columnsNum),i%columnsNum);
        }
         else
            gridLayout->addWidget(new QWidget(), qFloor(i/columnsNum),i%columnsNum);

    }
}

void GrpScreen::setTitle(QString txt)
{
    title = txt;

}

