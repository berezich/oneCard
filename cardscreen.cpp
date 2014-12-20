#include "cardscreen.h"

CardScreen::CardScreen(QScreen *screenInfo, QWidget *parent):BlankScreen(screenInfo,parent)
{
    spacingSize = spacingSize*scaleFactor;
    cardIconSize = cardIconSize*scaleFactor;
    leftCardOffset = leftCardOffset*scaleFactor;
    textCardNameSize = textCardNameSize*qSqrt(scaleFactor);
    leftNameCardOffset = leftNameCardOffset*scaleFactor;
    rightNextIconOffset = rightNextIconOffset*scaleFactor;
    nextIconSize = nextIconSize*scaleFactor;
    capSpacerH = capSpacerH*scaleFactor;

    //шапка
    cap = new Cap();


    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/plus.svg",":/svg/tools/plusPUSH.svg",QSize(55*scaleFactor,55*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    cap->addRightIcon(icon,capRightIconOffset);

    blankLayout->addWidget(cap);

    blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);


    cardListLayout = new QVBoxLayout();
    cardListLayout->setSpacing(spacingSize);
    //cardListLayout->addStretch();
    blankSpace->setLayout(cardListLayout);
    blankSpace->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    //SizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixe

    //blankLayout->addStretch();
}

void CardScreen::setTitle(QString txt)
{
    //title = txt;

}
CardScreen::~CardScreen()
{

}

void CardScreen::setCardList(QString title, QString grpImgSrc, QList<CardInfo> *cardList)
{
    QHBoxLayout *line;
    QLabel *cardIcon;
    QLabel *nameLbl;
    QLabel *nextIcon;
    CardInfo *card;
    QWidget *widgetLine;
    QWidget *space;

    this->title = title;
    cap->setTitle(title,titleLeftMargin,textTitleSize);

    SimpleIcon *icon = new SimpleIcon(0,grpImgSrc,grpImgSrc,QSize(55*scaleFactor,55*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(backPressed(int)));
    cap->addLeftIcon(icon,capLeftIconOffset);


    icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55*scaleFactor,55*scaleFactor));
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(backPressed(int)));
    cap->addLeftIcon(icon,capLeftIconOffset);




    for(int i=0; i<cardList->length(); i++)
    {
        line = new QHBoxLayout();
        //line->setAlignment(Qt::AlignTop);
        line->setAlignment( Qt::AlignTop);


        line->addSpacing(leftCardOffset);
        card = &(*cardList)[i];
        cardIcon = new SimpleIcon(card->getId(),card->getCardImgSrc(),"",cardIconSize);
        cardIcon-> setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        //cardIcon->adjustSize();
        //cardIcon->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        line->addWidget(cardIcon);

        nameLbl = new QLabel(card->getCardName());
        nameLbl->setFont(QFont("Calibri",textCardNameSize));
        nameLbl->setStyleSheet("QLabel { color : "+colorTextNameCard+"; }");
        nameLbl->setContentsMargins(leftNameCardOffset,0,0,0);
        nameLbl-> setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        //nameLbl->adjustSize();
        //nameLbl->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        line->addWidget(nameLbl);

        line->addStretch(1);

        nextIcon = new SimpleIcon(card->getId(),":/svg/tools/arrow.svg","",nextIconSize);
        nextIcon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        //nextIcon->adjustSize();
        //nextIcon->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        line->addWidget(nextIcon);
        line->addSpacing(rightNextIconOffset);

        widgetLine = new QWidget();
        widgetLine->setMinimumWidth(screenSize.width());
        //widgetLine->setMaximumHeight(cardIconSize.height());
        widgetLine->setLayout(line);

        //widgetLine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

        cardListLayout->addWidget(widgetLine);
    }
    //space = new QWidget();
    //cardListLayout->addWidget(space);
    //space->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    //cardListLayout->addSpacerItem(new QSpacerItem());
    cardListLayout->addStretch(1);

}

void CardScreen::onCapBack(int i)
{
    emit backPressed(i);

}

