#include "cardinfoscreen.h"

//CardInfoScreen::CardInfoScreen(QScreen *screenInfo, QWidget *parent):BlankScreen(screenInfo,parent)
CardInfoScreen::CardInfoScreen(QScreen *screenInfo,QSize appScrSize, QWidget *parent):BlankScreen(screenInfo,appScrSize,parent)

{
    spacingSize = spacingSize*scaleFactorH;
    cardIconSize = cardIconSize*scaleFactor;
    textCardNameSize = textCardNameSize*qSqrt(qSqrt(scaleFactor));

    rightEditIconOffset = rightEditIconOffset*scaleFactor;
    editIconSize = editIconSize*scaleFactor;
    infoIconSize = infoIconSize*scaleFactor;

    capSpacerH = capSpacerH*scaleFactorH;

    //шапка
    cap = new Cap(capHeight);
    cap->setTitle(title,textTitleSize,titleLeftMargin);
    //-------

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/sync.svg",":/svg/tools/syncPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    cap->addRightIcon(icon,capRightIconOffset);

    blankLayout->addWidget(cap);
    childWidgets.append(cap);
    blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

    cardInfoListLayout = new QVBoxLayout();
    cardInfoListLayout->setSpacing(spacingSize);

    blankSpace->setLayout(cardInfoListLayout);

    childLayouts.append(cardInfoListLayout);
    childLayouts.append(blankLayout);

    //blankLayout->addStretch();
}

CardInfoScreen::~CardInfoScreen()
{
    for(int i=0; i<childLayouts.length(); i++)
        if(childLayouts.at(i)!=NULL)
            delete(childLayouts.at(i));
    for(int i=0; i<childWidgets.length(); i++)
        if(childWidgets.at(i)!=NULL)
            delete(childWidgets.at(i));
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

    //cap->setTitle(title,titleLeftMargin,textTitleSize);

    cardInfoListLayout->setSpacing(spacingSize);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SLOT(onEditCard(int)));
    cap->addLeftIcon(icon,capLeftIconOffset);

    line = new QHBoxLayout();
    childLayouts.append(line);
    //для симметричности
    //line->addSpacing(editIconSize.width());

    //line->addStretch(1);

    nameEditLine = new QLineEdit(card->getCardName());
    nameEditLine->setObjectName("cardName");
    nameEditLine->setFont(QFont("Calibri",textCardNameSize));
    nameEditLine->setAlignment(Qt::AlignHCenter| Qt::AlignTop);
    nameEditLine->setReadOnly(true);
    //nameEditLine->setMaxLength();
    nameEditLine->setStyleSheet("border: 0px solid gray; border-radius: 10px; padding: 0 8px; background: "+backGroundColor+"; selection-background-color: darkgray;");
    connect( nameEditLine,SIGNAL(focusOutEvent(QFocusEvent*)),this,SLOT(onEditNameFinished));

    //cardName-------------------------
    line->addWidget(nameEditLine);
    childWidgets.append(nameEditLine);

    //line->addStretch(1);
    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",editIconSize);
    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    childWidgets.append(icon);
    line->addWidget(icon);
    line->addSpacing(rightEditIconOffset);

    widgetLine = new QWidget();
    widgetLine->setLayout(line);
    widgetLine->setMinimumWidth(screenSize.width());
    cardInfoListLayout->addWidget(widgetLine);
    childWidgets.append(widgetLine);
    connect(icon,SIGNAL(click(int)),this,SLOT(onEditName()));

    //frontside of card-------------------
    line = new QHBoxLayout();
    childLayouts.append(line);
    //для симметричности
    //line->addSpacing(editIconSize.width());

    line->addStretch(1);

    cardIcon = new SimpleIcon(0,card->getCardImgSrc(),"",cardIconSize);
    cardIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    line->addWidget(cardIcon);
    childWidgets.append(cardIcon);
    line->addStretch(1);

    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",editIconSize);
    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(editFrontSideImg()));
    line->addWidget(icon);
    childWidgets.append(icon);
    line->addSpacing(rightEditIconOffset);
    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(line);
    cardInfoListLayout->addWidget(widgetLine);
    childWidgets.append(widgetLine);

    //backside of card-----------------
    line = new QHBoxLayout();
    childLayouts.append(line);
    //для симметричности
    //line->addSpacing(editIconSize.width());
    line->addStretch(1);

    cardIcon = new SimpleIcon(0,card->getCardImgBackSrc(),"",cardIconSize);
    cardIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    line->addWidget(cardIcon);
    childWidgets.append(cardIcon);
    line->addStretch(1);

    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",editIconSize);
    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideImg()));
    line->addWidget(icon);
    childWidgets.append(icon);
    line->addSpacing(rightEditIconOffset);
    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(line);
    cardInfoListLayout->addWidget(widgetLine);
    childWidgets.append(widgetLine);
    //----------------------------------------


    line = new QHBoxLayout();
    childLayouts.append(line);
    //для симметричности
    //line->addSpacing(editIconSize.width());

    //line->addStretch(1);

    icon = new SimpleIcon(0,":/svg/tools/pen.svg",":/svg/tools/penPUSH.svg",infoIconSize);
    icon->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    line->addWidget(icon);
    childWidgets.append(icon);
    line->addSpacing(rightEditIconOffset + editIconSize.width());

    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    childWidgets.append(widgetLine);
    widgetLine->setLayout(line);

    cardInfoListLayout->addWidget(widgetLine);

    cardInfoListLayout->addStretch(1);
    //childLayouts.append(cardInfoListLayout);
    childWidgets.append(blankSpace);

    //childLayouts.append(blankLayout);
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

