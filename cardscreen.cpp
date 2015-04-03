#include "cardscreen.h"

CardScreen::CardScreen(QScreen *screenInfo, QSize appScrSize , int colorName, DATA_SOURCE srcType, QWidget *parent):BlankScreen(screenInfo,appScrSize, colorName,parent)
{
    init();
    this->srcType = srcType;
    spacingSize = spacingSize*scaleFactor;
    cardIconSize = cardIconSize*scaleFactor;
    leftCardOffset = leftCardOffset*scaleFactor;
    textCardNameSize = textCardNameSize*qSqrt(scaleFactor);
    leftNameCardOffset = leftNameCardOffset*scaleFactor;
    rightNextIconOffset = rightNextIconOffset*scaleFactor;
    nextIconSize = nextIconSize*scaleFactor;
    capSpacerH = capSpacerH*scaleFactor;

    //cap
    cap = new Cap(capHeight, skinColor);
    this->colorName = colorName;

    if(srcType==LOCAL)
    {
        SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/plus.svg","",QSize(55,55)*scaleFactor);
        icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(addCardSelected()));
        cap->addRightIcon(icon,capRightIconOffset);
    }

    blankLayout->addWidget(cap);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);
    setLayout(blankLayout);


    QVBoxLayout *blankSpaceLayout = new QVBoxLayout(blankSpace);
    blankSpace->setLayout(blankSpaceLayout);
    blankSpaceLayout->setContentsMargins(0,0,0,0);

    scroll = new QScrollArea(blankSpace);
    blankSpaceLayout->addWidget(scroll);
    scroll->horizontalScrollBar()->hide();
    scrollBar = scroll->verticalScrollBar();

    cardLstWidget = new QWidget(scroll);
    cardLstWidget->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Expanding);

    scroll->setWidget(cardLstWidget);
    scroll->setWidgetResizable(true);


    cardListLayout = new QVBoxLayout();
    cardListLayout->setSpacing(spacingSize);
    cardLstWidget->setLayout(cardListLayout);
}

CardScreen::~CardScreen()
{
    while(children().length()>0)
            if(children().last())
                delete(children().last());
}

void CardScreen::setCardList(QString title, QString grpImgSrc, QList<CardInfo> *cardList, bool isSwipe)
{
    QHBoxLayout *line;
    ImgIcon *cardIcon;
    QLabel *nameLbl;
    QLabel *nextIcon;
    CardInfo *card;
    QWidget *widgetLine;

    this->cardList = cardList;
    this->title = title;
    cap->setTitle(title,textTitleSize,titleLeftMargin);

    SimpleIcon *icon = new SimpleIcon(0,grpImgSrc,grpImgSrc,QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(backPressed(int)));
    cap->addLeftIcon(icon,capLeftIconOffset);


    icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(backPressed(int)));
    cap->addLeftIcon(icon,capLeftIconOffset);




    for(int i=0; i<cardList->length(); i++)
    {
        line = new QHBoxLayout();
        line->setAlignment( Qt::AlignTop);

        line->addSpacing(leftCardOffset);
        card = &(*cardList)[i];
        if(card->getCardImgSrc()=="" || (srcType==SERVER && !card->isImgLocal()))
            cardIcon = new ImgIcon(card->getId(),InterFace::getSkinColor(colorName).iconFolder() + imgNoPhotoSrc,cardIconSize,false);
        else
            cardIcon = new ImgIcon(card->getId(),card->getCardImgSrc(),cardIconSize,false);
        connect(cardIcon,SIGNAL(click(int)),this,SIGNAL(cardSelected(int)));
        cardIcon-> setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        line->addWidget(cardIcon);

        nameLbl = new QLabel(card->getCardName());
        nameLbl->setFont(QFont("Calibri",textCardNameSize));
        nameLbl->setStyleSheet("QLabel { color : "+colorTextNameCard+"; }");
        nameLbl-> setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        line->addWidget(nameLbl);
        line->addStretch(10);

        if(srcType==SERVER && !card->isImgLocal())
            nextIcon = new SimpleIcon(card->getId(),InterFace::getSkinColor(colorName).iconFolder() + "load.svg","",nextIconSize);
        else
            nextIcon = new SimpleIcon(card->getId(),InterFace::getSkinColor(colorName).iconFolder() + "arrow.svg","",nextIconSize);
        nextIcon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        connect(nextIcon,SIGNAL(click(int)),this,SIGNAL(cardSelected(int)));
        line->addWidget(nextIcon);
        line->addSpacing(rightNextIconOffset);

        widgetLine = new QWidget();

        widgetLine->setMinimumWidth(screenSize.width());
        widgetLine->setLayout(line);
        cardListLayout->addWidget(widgetLine);
    }
    cardListLayout->addStretch(1);
    adjustSize();
    cardLstWidget->adjustSize();
    if(isSwipe && (cardLstWidget->size().height()>screenSize.height()-capHeight))
    {
        swipeCover = new SwipeCover(screenSize.height()-capHeight,cardLstWidget->size().height() - (screenSize.height()-capHeight),scrollBar,blankSpace);
        connect(swipeCover,SIGNAL(onClick(QPoint)),this,SLOT(onClickPos(QPoint)));
    }

}


void CardScreen::onCapBack(int i)
{
    emit backPressed(i);

}

void CardScreen::onClickPos(QPoint pos)
{
    if(pos.y()>0 && pos.x()>0)
    {
        int lineHeigt = cardLstWidget->size().height()/cardList->length();
        int iCard = pos.y()/lineHeigt;
        if(iCard<cardList->length())
            emit cardSelected((*cardList)[iCard].getId());
    }

}

void CardScreen::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Back )
        emit backPressed(0);
}

