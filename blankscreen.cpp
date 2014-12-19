#include "blankscreen.h"

BlankScreen::BlankScreen(QScreen *screenInfo, QWidget *parent):QWidget(parent)
//BlankScreen::BlankScreen(QScreen *screenInfo)
{
//    this->screenInfo = screenInfo;
//    screenSize = screenInfo->geometry().size();
//    scaleFactor = screenSize.width()/defaultWidth;
//    capHeight = capHeight*scaleFactor;
//    qDebug()<<"scale = "<< scaleFactor;
//    setMinimumSize(screenSize);

    this->screenInfo = screenInfo;
    screenSize = screenInfo->geometry().size();
    scaleFactor = screenSize.width()/defaultWidth;

    qDebug()<<"scale = "<< scaleFactor;


    capHeight = capHeight*scaleFactor;
    titleLeftMargin =titleLeftMargin*scaleFactor;
    textTitleSize = textTitleSize*qSqrt(scaleFactor);
    capSpacerH = capSpacerH * scaleFactor;
    capRightIconOffset = capRightIconOffset*scaleFactor;

    setMinimumSize(screenSize);

    blankLayout = new QBoxLayout(QBoxLayout::TopToBottom,this);


    blankLayout->setSpacing(0);
    blankLayout->setMargin(0);

    //шапка
    cap = new Cap();
    cap->setTitle(title,titleLeftMargin,textTitleSize);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/oblako.svg",":/svg/tools/oblakoPUSH.svg",QSize(80*scaleFactor,40*scaleFactor));

    cap->addRightIcon(icon,capRightIconOffset);

    blankLayout->addWidget(cap);

    blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

//    QWidget *space = new QWidget();
//    space->setLayout(gridLayout);
//    blankLayout->addWidget(space);

//    setLayout(blankLayout);

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
//    blankLayout->addStretch();




//    Icon *icon1 = new Icon(gr1->getId(),gr1->getName(), gr1->getImgSrc(), gr1->setImgPushSrc(), new QSize(180*scaleFactor,180*scaleFactor), new QSize(230*scaleFactor,210*scaleFactor));
//    Icon *icon2 = new Icon(gr2->getId(),gr2->getName(), gr2->getImgSrc(), gr2->setImgPushSrc(), new QSize(180*scaleFactor,180*scaleFactor), new QSize(230*scaleFactor,210*scaleFactor));
//    Icon *icon3 = new Icon(gr3->getId(),gr3->getName(), gr3->getImgSrc(), gr3->setImgPushSrc(), new QSize(180*scaleFactor,180*scaleFactor), new QSize(230*scaleFactor,210*scaleFactor));
//    Icon *icon4 = new Icon(gr4->getId(),gr4->getName(), gr4->getImgSrc(), gr4->setImgPushSrc(), new QSize(180*scaleFactor,180*scaleFactor), new QSize(230*scaleFactor,210*scaleFactor));
//    Icon *icon5 = new Icon(gr5->getId(),gr5->getName(), gr5->getImgSrc(), gr5->setImgPushSrc(), new QSize(180*scaleFactor,180*scaleFactor), new QSize(230*scaleFactor,210*scaleFactor));


}

BlankScreen::~BlankScreen()
{

}

