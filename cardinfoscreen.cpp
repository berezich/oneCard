#include "cardinfoscreen.h"

CardInfoScreen::CardInfoScreen(QScreen *screenInfo, QWidget *parent):BlankScreen(screenInfo,parent)
{
    spacingSize = spacingSize*scaleFactor;
    cardIconSize = cardIconSize*scaleFactor;
    textCardNameSize = textCardNameSize*qSqrt(scaleFactor);

    rightEditIconOffset = rightEditIconOffset*scaleFactor;
    editIconSize = editIconSize*scaleFactor;

    capSpacerH = capSpacerH*scaleFactor;

    //шапка
    cap = new Cap();
    cap->setTitle(title,titleLeftMargin,textTitleSize);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/sync.svg",":/svg/tools/syncPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    cap->addRightIcon(icon,capRightIconOffset);

    blankLayout->addWidget(cap);

    blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

    cardInfoListLayout = new QVBoxLayout();
    cardInfoListLayout->setSpacing(spacingSize);
    blankSpace->setLayout(cardInfoListLayout);

    //blankSpace->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    //SizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixe
    //blankLayout->addStretch();
}

CardInfoScreen::~CardInfoScreen()
{

}

void CardInfoScreen::showCardInfo(CardInfo *card)
{
    QHBoxLayout *line;
    SimpleIcon *cardIcon;
    QLabel *nameLbl;
    QLabel *editIcon;
    //CardInfo *card;
    QWidget *widgetLine;
    //SimpleIcon *icon;


    //this->title = title;
    //cap->setTitle(title,titleLeftMargin,textTitleSize);

    cardInfoListLayout->setSpacing(0);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(backPressed(int)));
    cap->addLeftIcon(icon,capLeftIconOffset);

    line = new QHBoxLayout();
    line->addStretch(1);
    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",editIconSize*scaleFactor);
    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    icon->setMargin(15);
    line->addWidget(icon);
    widgetLine = new QWidget();
    widgetLine->setLayout(line);
    cardInfoListLayout->addWidget(widgetLine);

    QLineEdit *eLine = new QLineEdit(card->getCardName());
    eLine->setFont(QFont("Calibri",textCardNameSize));
    eLine->setAlignment(Qt::AlignHCenter| Qt::AlignTop);
    eLine->setReadOnly(true);
    eLine->setStyleSheet("border: 0px solid gray; border-radius: 10px; padding: 0 8px; background: "+backGroundColor+"; selection-background-color: darkgray;");
    cardInfoListLayout->addWidget(eLine);

    line = new QHBoxLayout();
    line->addStretch(1);
    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",editIconSize*scaleFactor);
    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    icon->setMargin(15);
    line->addWidget(icon);
    widgetLine = new QWidget();
    widgetLine->setLayout(line);
    cardInfoListLayout->addWidget(widgetLine);

    cardIcon = new SimpleIcon(0,card->getCardImgSrc(),"",cardIconSize);
    cardIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    cardInfoListLayout->addWidget(cardIcon);

    cardInfoListLayout->addStretch(1);
    /*
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
    cardListLayout->addStretch(1);
    */
}

