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
    imgSrc = card->getCardImgSrc();
    cardInfo = card;

    //this->title = title;
    //cap->setTitle(title,titleLeftMargin,textTitleSize);

    cardInfoListLayout->setSpacing(spacingSize);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SLOT(onEditCard(int)));
    cap->addLeftIcon(icon,capLeftIconOffset);

    line = new QHBoxLayout();
    line->addSpacing(editIconSize.width()*scaleFactor);

    line->addStretch(1);

    nameEditLine = new QLineEdit(card->getCardName());
    nameEditLine->setFont(QFont("Calibri",textCardNameSize));
    nameEditLine->setAlignment(Qt::AlignHCenter| Qt::AlignTop);
    nameEditLine->setReadOnly(true);
    nameEditLine->setStyleSheet("border: 0px solid gray; border-radius: 10px; padding: 0 8px; background: "+backGroundColor+"; selection-background-color: darkgray;");
    connect( nameEditLine,SIGNAL(focusOutEvent(QFocusEvent*)),this,SLOT(onEditNameFinished));
    line->addWidget(nameEditLine);
    //cardInfoListLayout->addWidget(nameEditLine);

    line->addStretch(1);
    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",editIconSize*scaleFactor);
    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);

    line->addWidget(icon);
    line->addSpacing(rightEditIconOffset);
    widgetLine = new QWidget();
    widgetLine->setLayout(line);
    widgetLine->setMinimumWidth(screenSize.width());
    cardInfoListLayout->addWidget(widgetLine);
    connect(icon,SIGNAL(click(int)),this,SLOT(onEditName()));


    line = new QHBoxLayout();
    line->addSpacing(editIconSize.width()*scaleFactor);
    line->addStretch(1);

    cardIcon = new SimpleIcon(0,card->getCardImgSrc(),"",cardIconSize);
    cardIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    line->addWidget(cardIcon);
    line->addStretch(1);

    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",editIconSize*scaleFactor);
    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    line->addWidget(icon);
    line->addSpacing(rightEditIconOffset);
    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(line);
    cardInfoListLayout->addWidget(widgetLine);






    cardInfoListLayout->addStretch(1);

}

void CardInfoScreen::onEditName()
{
    nameEditLine->setReadOnly(!nameEditLine->isReadOnly());
    nameEditLine->setFocus();
}

void CardInfoScreen::onEditCard(int i)
{
    emit editCard(nameEditLine->text(),imgSrc);
    cardInfo->setCardName(nameEditLine->text());
    cardInfo->setCardImgSrc(imgSrc);
    emit backPressed(0);
}

