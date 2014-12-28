#include "grpscreen.h"

GrpScreen::GrpScreen(QScreen *screenInfo,QSize appScrSize, QWidget *parent):BlankScreen(screenInfo,appScrSize,parent)

{

    //шапка
    cap = new Cap(capHeight);
    cap->setTitle(title,textTitleSize,titleLeftMargin);

    SimpleIcon *icon = new SimpleIcon(0,":svg/tools/menuicon.svg","",QSize(50*scaleFactor,25*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    cap->addLeftIcon(icon,capLeftIconOffset);
    connect(icon,SIGNAL(click(int)),this,SLOT(onMenuClick()));

    icon = new SimpleIcon(0,":/svg/tools/oblako.svg",":/svg/tools/oblakoPUSH.svg",QSize(80*scaleFactor,40*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    cap->addRightIcon(icon,capRightIconOffset);
    blankLayout->setContentsMargins(0,0,0,0);
    blankLayout->addWidget(cap);

    //blankLayout->addSpacing(capSpacerH);

    blankSpace = new BlankSpace(QSize(appScrSize.width(),appScrSize.height()-capHeight), scaleFactor,this);

    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

    iconSize = iconSize*scaleFactor;
    textSize = textSize*qSqrt(qSqrt(scaleFactor));

    gridLayout = new QGridLayout(this);
    blankSpace->setLayout(gridLayout);




    blankLayout->addStretch();
}

void GrpScreen::showMenu()
{
    blankSpace->showMenu();
}
void GrpScreen::initMenu()
{
    blankSpace->initMenu();
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
            icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpLst[i].getImgSrc(), grpLst[i].getImgPushSrc(), iconSize, QSize(screenSize.width()/3,0));
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

void GrpScreen::onMenuClick()
{
    blankSpace->showMenu();
}

