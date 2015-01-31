#include "cardscreen.h"

//CardScreen::CardScreen(QScreen *screenInfo, QWidget *parent):BlankScreen(screenInfo,parent)
CardScreen::CardScreen(QScreen *screenInfo,QSize appScrSize , SKIN_COLOR_NAME colorName, QWidget *parent):BlankScreen(screenInfo,appScrSize, colorName,parent)
{
    init();
    spacingSize = spacingSize*scaleFactor;
    cardIconSize = cardIconSize*scaleFactor;
    leftCardOffset = leftCardOffset*scaleFactor;
    textCardNameSize = textCardNameSize*qSqrt(scaleFactor);
    leftNameCardOffset = leftNameCardOffset*scaleFactor;
    rightNextIconOffset = rightNextIconOffset*scaleFactor;
    nextIconSize = nextIconSize*scaleFactor;
    capSpacerH = capSpacerH*scaleFactor;

    //шапка
    cap = new Cap(capHeight, skinColor);

    childWidgets.append(cap);
    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/plus.svg",":/svg/tools/plusPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(addCardSelected()));
    cap->addRightIcon(icon,capRightIconOffset);

    childLayouts.append(blankLayout);
    blankLayout->addWidget(cap);

    blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);


    cardListLayout = new QVBoxLayout();
    childLayouts.append(cardListLayout);
    cardListLayout->setSpacing(spacingSize);
    //cardListLayout->addStretch();
    blankSpace->setLayout(cardListLayout);
    blankSpace->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    //SizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixe

    //blankLayout->addStretch();
}

CardScreen::~CardScreen()
{
    for(int i=0; i<childLayouts.length(); i++)
        if(childLayouts.at(i)!=NULL)
            delete(childLayouts.at(i));
    for(int i=0; i<childWidgets.length(); i++)
        if(childWidgets.at(i)!=NULL)
            delete(childWidgets.at(i));
}

void CardScreen::setCardList(QString title, QString grpImgSrc, QList<CardInfo> *cardList)
{
    QHBoxLayout *line;
    QLabel *cardIcon;
    QLabel *nameLbl;
    QLabel *nextIcon;
    CardInfo *card;
    QWidget *widgetLine;

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
        childLayouts.append(line);
        line->setAlignment( Qt::AlignTop);

        line->addSpacing(leftCardOffset);
        card = &(*cardList)[i];
        if(card->getCardImgSrc()!="")
            cardIcon = new SimpleIcon(card->getId(),card->getCardImgSrc(),"",cardIconSize);
        else
            cardIcon = new SimpleIcon(card->getId(),imgNoPhotoSrc,"",cardIconSize);
        cardIcon-> setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        line->addWidget(cardIcon);
        childWidgets.append(cardIcon);

        nameLbl = new QLabel(card->getCardName());
        nameLbl->setFont(QFont("Calibri",textCardNameSize));
        nameLbl->setStyleSheet("QLabel { color : "+colorTextNameCard+"; }");
        //nameLbl->setContentsMargins(leftNameCardOffset,0,0,0);
        nameLbl-> setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

        line->addWidget(nameLbl);
        childWidgets.append(nameLbl);

        line->addStretch(10);

        nextIcon = new SimpleIcon(card->getId(),":/svg/tools/arrow.svg","",nextIconSize);
        nextIcon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        connect(nextIcon,SIGNAL(click(int)),this,SIGNAL(cardSelected(int)));
        line->addWidget(nextIcon);
        childWidgets.append(nextIcon);
        line->addSpacing(rightNextIconOffset);

        widgetLine = new QWidget();

        widgetLine->setMinimumWidth(screenSize.width());
        widgetLine->setLayout(line);

        childWidgets.append(widgetLine);

        cardListLayout->addWidget(widgetLine);
    }
    cardListLayout->addStretch(1);
    childWidgets.append(blankSpace);

}

void CardScreen::onCapBack(int i)
{
    emit backPressed(i);

}

void CardScreen::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Back )
        emit backPressed(0);
}

