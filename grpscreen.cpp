#include "grpscreen.h"

GrpScreen::GrpScreen(QScreen *screenInfo,QSize appScrSize, QWidget *parent):BlankScreen(screenInfo,appScrSize,parent)

{

    iconSize = iconSize*scaleFactor;
    textSize = textSize*qSqrt(qSqrt(scaleFactor));

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

    blankSpace = new QWidget(this);
    blankLayout->addWidget(blankSpace);

    QVBoxLayout *blankSpaceLayout = new QVBoxLayout(blankSpace);
    blankSpace->setLayout(blankSpaceLayout);
    blankSpaceLayout->setContentsMargins(0,0,0,0);

    scroll = new QScrollArea(blankSpace);
    blankSpaceLayout->addWidget(scroll);
    scroll->horizontalScrollBar()->hide();

    gridWidget = new QWidget(scroll);
    gridWidget->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Expanding);

    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(0);
    gridWidget->setLayout(gridLayout);

    scroll->setWidget(gridWidget);
    scroll->setWidgetResizable(true);

}


GrpScreen::~GrpScreen()
{

}

void GrpScreen::setGrpLst(QList<Grp> grpLst)
{
    Icon *icon;
    int numItems = columnsNum*rowsNum;
    if(numItems < grpLst.length())
        numItems = grpLst.length();
    QSize gridItemSize = QSize(screenSize.width()/columnsNum,(screenSize.height()-capHeight)/rowsNum - 10*scaleFactor);

    for(int i=0; i<numItems; i++)
    {
        if(i < grpLst.length())
        {
            icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpLst[i].getImgSrc(), grpLst[i].getImgPushSrc(), iconSize, gridItemSize);
            connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickGrpIcon(int)));
            gridLayout->addWidget(icon, qFloor(i/columnsNum),i%columnsNum);
        }
        else
            gridLayout->addWidget(new QWidget(), qFloor(i/columnsNum),i%columnsNum);

    }

    //blankSpace->adjustSize();
}

void GrpScreen::initMenu()
{
    menuWidget = new Menu(QSize(screenSize.width(),screenSize.height()-capHeight),scaleFactor,blankSpace);
    menuWidget->hide();
}

void GrpScreen::onKeyBackPressed(QKeyEvent *event)
{
    if(menuWidget->isMenuOpen())
        menuWidget->showMainMenu();
    else
        QWidget::keyPressEvent(event);
}



void GrpScreen::onClickGrpIcon(int grpId)
{
    emit selectLocalGrp(grpId);
}

void GrpScreen::onMenuClick()
{
    menuWidget->showMainMenu();
}

