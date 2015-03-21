#include "grpscreen.h"

GrpScreen::GrpScreen(QWidget *parent):BlankScreen(parent)
{

}

GrpScreen::GrpScreen(QScreen *screenInfo,QSize appScrSize, int colorName, QWidget *parent):BlankScreen(screenInfo,appScrSize, colorName,parent)
{
    init();
    iconSize = iconSize*scaleFactor;
    iconPlusSize = iconPlusSize*scaleFactor;
    textSize = textSize*qSqrt(qSqrt(scaleFactor));
    this->colorName = colorName;
    //шапка
    cap = new Cap(capHeight, skinColor);
    cap->setTitle(title,textTitleSize,titleLeftMargin);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg","",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    cap->addLeftIcon(icon,capLeftIconOffset);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(backPressed()));
    /*
    SimpleIcon *icon = new SimpleIcon(0,":svg/tools/menuicon.svg","",QSize(50*scaleFactor,25*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    cap->addLeftIcon(icon,capLeftIconOffset);
    connect(icon,SIGNAL(click(int)),this,SLOT(onMenuClick()));
    */

    /*
    icon = new SimpleIcon(0,":/svg/tools/oblako.svg",":/svg/tools/oblakoPUSH.svg",QSize(80*scaleFactor,40*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    cap->addRightIcon(icon,capRightIconOffset);
    */

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
    scrollBar = scroll->verticalScrollBar();


}


GrpScreen::~GrpScreen()
{
    while(children().length()>0)
        if(children().last())
            delete(children().last());
}

void GrpScreen::setGrpLst(QList<Grp> grpLst, QString grpIconPath, bool isSwipe, bool editable)
{
    Icon *icon;
    int numItems = columnsNum*rowsNum;
    clearGrid();
    this->grpLst = grpLst;

    if(numItems <= grpLst.length())
    {
        numItems = grpLst.length();
        if(editable)
            numItems++;
    }

    gridItemSize = QSize(screenSize.width()/columnsNum,(screenSize.height()-capHeight)/rowsNum );

    for(int i=0; i<numItems; i++)
    {
        if(i < grpLst.length())
        {
            icon = new Icon(grpLst[i].getId(),grpLst[i].getName(),textSize, grpIconPath+grpLst[i].getImgSrc(), "", iconSize, gridItemSize);
            connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickGrpIcon(int)));
            gridLayout->addWidget(icon, qFloor(i/columnsNum),i%columnsNum);
            //qDebug()<<"Name: "<<grpLst[i].getName()<<"grpId: "<<grpLst[i].getId();
        }
        else if(i == grpLst.length()&&editable)
        {
            icon = new Icon(-1,"",-1, InterFace::getSkinColor(colorName).iconFolder()+"plus.svg", "", iconPlusSize, gridItemSize);
            connect(icon,SIGNAL(clickIcon(int)),this,SLOT(onClickGrpIcon(int)));

            gridLayout->addWidget(icon, qFloor(i/columnsNum),i%columnsNum);
        }
        else
            gridLayout->addWidget(new QWidget(), qFloor(i/columnsNum),i%columnsNum);

    }
    adjustSize();
    gridWidget->adjustSize();

    if(isSwipe)
    {
        swipeCover = new SwipeCover(screenSize.height()-capHeight,gridWidget->size().height() - (screenSize.height()-capHeight),scrollBar,blankSpace);
        connect(swipeCover,SIGNAL(onClick(QPoint)),this,SLOT(onClickPos(QPoint)));
    }
    //blankSpace->adjustSize();
}

void GrpScreen::clearGrid()
{
    while(gridWidget->children().length()>0)
        if(gridWidget->children().last())
            delete(gridWidget->children().last());

    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(0);
    gridWidget->setLayout(gridLayout);
}
/*
void GrpScreen::initMenu()
{
    menuWidget = new Menu(QSize(screenSize.width(),screenSize.height()-capHeight),scaleFactor,sett,blankSpace);
    menuWidget->hide();
}

void GrpScreen::onKeyBackPressed(QKeyEvent *event)
{
    if(menuWidget->isMenuOpen())
        menuWidget->showMainMenu();
    else
        QWidget::keyPressEvent(event);
}
*/


void GrpScreen::onClickGrpIcon(int grpId)
{
    emit selectLocalGrp(grpId);
}

void GrpScreen::onClickPos(QPoint pos)
{
    if(pos.y()>= 0 && pos.x() >= 0)
    {
        int iRow = qFloor(pos.y()/gridItemSize.height());
        int iCol = qFloor(pos.x()/gridItemSize.width());
        int iGrp = iRow*columnsNum + iCol;
        if(iGrp<grpLst.length())
        {

            onClickGrpIcon(grpLst[iGrp].getId());
        }
        else if( iGrp == grpLst.length())
            onClickGrpIcon(-1); //new Grp
    }

}
/*
void GrpScreen::onMenuClick()
{
    menuWidget->showMainMenu();
}
*/
