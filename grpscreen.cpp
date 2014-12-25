#include "grpscreen.h"

//GrpScreen::GrpScreen(QScreen *screenInfo, QWidget *parent):BlankScreen(screenInfo,parent)
GrpScreen::GrpScreen(QScreen *screenInfo,QSize appScrSize, QWidget *parent):BlankScreen(screenInfo,appScrSize,parent)

{
    //iconHeight = iconHeight*scaleFactor;
    //iconWidth = iconWidth*scaleFactor;

    //шапка
    cap = new Cap(capHeight);
    cap->setTitle(title,textTitleSize,titleLeftMargin);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/oblako.svg",":/svg/tools/oblakoPUSH.svg",QSize(80*scaleFactor,40*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    cap->addRightIcon(icon,capRightIconOffset);

    blankLayout->addWidget(cap);

    blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

    iconSize = iconSize*scaleFactor;
    textSize = textSize*qSqrt(qSqrt(scaleFactor));

    gridLayout = new QGridLayout(this);
    blankSpace->setLayout(gridLayout);


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
            connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickGrpIcon(int)));
            gridLayout->addWidget(icon, qFloor(i/columnsNum),i%columnsNum);
        }
        else
            gridLayout->addWidget(new QWidget(), qFloor(i/columnsNum),i%columnsNum);

    }
}

void GrpScreen::onClickGrpIcon(int grpId)
{
    emit selectLocalGrp(grpId);
}

