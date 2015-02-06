#include "cardinfoscreen.h"

CardInfoScreen::CardInfoScreen(QScreen *screenInfo,QSize appScrSize, int colorName, QWidget *parent):BlankScreen(screenInfo,appScrSize, colorName,parent)
{
    init();
    spacingSize = spacingSize*scaleFactorH;
    cardIconSize = cardIconSize*scaleFactor;
    textCardNameSize = textCardNameSize*qSqrt(qSqrt(scaleFactor));
    textMagnetLineSize = textMagnetLineSize*qSqrt(qSqrt(scaleFactor));

    rightEditIconOffset = rightEditIconOffset*scaleFactor;
    editIconSize = editIconSize*scaleFactor;
    infoIconSize = infoIconSize*scaleFactor;

    capSpacerH = capSpacerH*scaleFactorH;
    iconsFolder = InterFace::getSkinColor(colorName).iconFolder();
    //шапка
    cap = new Cap(capHeight, skinColor);
    cap->setTitle(title,textTitleSize,titleLeftMargin);
    //-------

    /*
    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/sync.svg",":/svg/tools/syncPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    cap->addRightIcon(icon,capRightIconOffset);
    */

    blankLayout->addWidget(cap);
    childWidgets.append(cap);
    blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

    cardInfoListLayout = new QVBoxLayout();
    cardInfoListLayout->setSpacing(spacingSize);
    cardInfoListLayout->setContentsMargins(0,0,0,0);

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
    magnetLineEdit=NULL;
}

void CardInfoScreen::showCardInfo(CardInfo *card, DATA_SOURCE dataSrc)
{
    QHBoxLayout *line;
    SimpleIcon *cardIcon;
    QWidget *widgetLine;
    imgSrc = card->getCardImgSrc();
    cardInfo = card;

    //cap->setTitle(title,titleLeftMargin,textTitleSize);

    cardInfoListLayout->setSpacing(spacingSize);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SLOT(onEditCard()));
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
    nameEditLine->setMaxLength(14);
    nameEditLine->setStyleSheet("border: 0px; background: "+backGroundColor+";");
    //connect( nameEditLine,SIGNAL(focusOutEvent(QFocusEvent*)),this,SLOT(onEditNameFinished));

    //cardName-------------------------
    line->addWidget(nameEditLine);
    childWidgets.append(nameEditLine);

    if(dataSrc == LOCAL)
    {
        //line->addStretch(1);
        icon = new SimpleIcon(0,iconsFolder+"pen.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        childWidgets.append(icon);
        line->addWidget(icon);
        line->addSpacing(rightEditIconOffset);
    }

    widgetLine = new QWidget();
    widgetLine->setLayout(line);
    widgetLine->setMinimumWidth(screenSize.width());
    cardInfoListLayout->addWidget(widgetLine);
    childWidgets.append(widgetLine);
    connect(icon,SIGNAL(click(int)),this,SLOT(onEditName()));

    //frontside of card-------------------
    line = new QHBoxLayout();

    //для симметричности
    //line->addSpacing(editIconSize.width());

    line->addStretch(1);

    if(card->getCardImgSrc()!="")
        cardIcon = new SimpleIcon(0,card->getCardImgSrc(),"",cardIconSize);
    else
        cardIcon = new SimpleIcon(0,iconsFolder+imgNoPhotoSrc,"",cardIconSize);
    cardIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    line->addWidget(cardIcon);
    childWidgets.append(cardIcon);
    line->addStretch(1);
    QWidget *vLineWidget;
    QVBoxLayout *vLine;
    if(dataSrc == LOCAL)
    {

        vLineWidget = new QWidget();
        vLine = new QVBoxLayout();
        vLineWidget->setLayout(vLine);
        vLine->setContentsMargins(0,0,0,0);
        childLayouts.append(vLine);
        childLayouts.append(line);


        icon = new SimpleIcon(0,iconsFolder+"photo.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editFrontSideCameraImg()));
        vLine->addWidget(icon);
        childWidgets.append(icon);

        icon = new SimpleIcon(0,iconsFolder+"gallery.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editFrontSideGalleryImg()));
        vLine->addWidget(icon);
        line->addWidget(vLineWidget);
        childWidgets.append(icon);

        vLine->addStretch(1);
        childWidgets.append(vLineWidget);

        line->addSpacing(rightEditIconOffset);
    }

    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(line);
    cardInfoListLayout->addWidget(widgetLine);
    childWidgets.append(widgetLine);

    //backside of card-----------------
    line = new QHBoxLayout();
    //для симметричности
    //line->addSpacing(editIconSize.width());
    line->addStretch(1);

    //cardIcon = new SimpleIcon(0,card->getCardImgBackSrc(),"",cardIconSize);
    if(card->getCardImgBackSrc()!="")
        cardIcon = new SimpleIcon(0,card->getCardImgBackSrc(),"",cardIconSize);
    else
        cardIcon = new SimpleIcon(0,iconsFolder+imgNoPhotoSrc,"",cardIconSize);

    cardIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    line->addWidget(cardIcon);
    childWidgets.append(cardIcon);
    line->addStretch(1);
    if(dataSrc == LOCAL)
    {
        vLineWidget = new QWidget();
        vLine = new QVBoxLayout();
        vLineWidget->setLayout(vLine);
        vLine->setContentsMargins(0,0,0,0);
        childLayouts.append(vLine);
        childLayouts.append(line);

        icon = new SimpleIcon(0,iconsFolder+"photo.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideCameraImg()));
        vLine->addWidget(icon);
        childWidgets.append(icon);

        icon = new SimpleIcon(0,iconsFolder+"gallery.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideGalleryImg()));
        vLine->addWidget(icon);
        line->addWidget(vLineWidget);
        childWidgets.append(icon);

        vLine->addStretch(1);
        childWidgets.append(vLineWidget);

    //    icon = new SimpleIcon(0,":/svg/tools/infophoto.svg",":/svg/tools/infophotoPUSH.svg",editIconSize);
    //    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    //    connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideCameraImg()));
    //    line->addWidget(icon);
    //    childWidgets.append(icon);


        line->addSpacing(rightEditIconOffset);
    }
    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(line);
    cardInfoListLayout->addWidget(widgetLine);
    childWidgets.append(widgetLine);
    //----------------------------------------

    //magnet line-----------------------------
    lineMagnetLayout = new QHBoxLayout();
    childLayouts.append(lineMagnetLayout);
    //для симметричности
    //line->addSpacing(editIconSize.width());

    lineMagnetLayout->addStretch(1);

    if(card->getIsMagnetLine())
        iconMagnet = new SimpleIcon(0,":/svg/tools/magnetyes.svg","",infoIconSize);
    else
        iconMagnet = new SimpleIcon(0,":/svg/tools/magnetno.svg","",infoIconSize);

    //iconMagnet->setAlignment(Qt::AlignCenter);
    iconMagnet->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
    lineMagnetLayout->addWidget(iconMagnet);
    childWidgets.append(iconMagnet);

    if(dataSrc == LOCAL)
    {
        magnetLineEdit = new QLineEdit(card->getMagnet());
        magnetLineEdit->setFont(QFont("Calibri",textMagnetLineSize));
        magnetLineEdit->setAlignment(Qt::AlignHCenter| Qt::AlignTop);
        magnetLineEdit->setReadOnly(false);
        //magnetLineEdit->setMaxLength(14);
        magnetLineEdit->setStyleSheet("border: "+QString::number(scaleFactor)+"px solid gray; border-radius: "+QString::number(15*scaleFactor)+"px; padding: 0 0px; background: #ffffff;");
        if(!card->getIsMagnetLine())
            magnetLineEdit->hide();
        lineMagnetLayout->addWidget(magnetLineEdit);
        childWidgets.append(magnetLineEdit);
    }

    //line->addSpacing(rightEditIconOffset + editIconSize.width());

    lineMagnetLayout->addStretch(1);

    if(dataSrc == LOCAL)
    {
        icon = new SimpleIcon(0,iconsFolder+"pen.svg","",editIconSize);
        icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SLOT(editFlagMagnetLine()));
        lineMagnetLayout->addWidget(icon);
        childWidgets.append(icon);
        lineMagnetLayout->addSpacing(rightEditIconOffset);
    }

    widgetLine = new QWidget();
    //widgetLine->setStyleSheet("border: 1px solid gray;");
    widgetLine->setMinimumWidth(screenSize.width());
    childWidgets.append(widgetLine);
    widgetLine->setLayout(lineMagnetLayout);

    cardInfoListLayout->addWidget(widgetLine);



    /*
    //save-------------------------------
    line = new QHBoxLayout();
    childLayouts.append(line);

    icon = new SimpleIcon(0,":/svg/tools/save.svg","",infoIconSize);

    icon->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    line->addWidget(icon);
    childWidgets.append(icon);
    line->addSpacing(editIconSize.width()+rightEditIconOffset);

    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    childWidgets.append(widgetLine);
    widgetLine->setLayout(line);

    cardInfoListLayout->addWidget(widgetLine);

    //-----------------------------------
*/
    cardInfoListLayout->addStretch(1);
    //childLayouts.append(cardInfoListLayout);
    childWidgets.append(blankSpace);

    //childLayouts.append(blankLayout);
}

void CardInfoScreen::onEditName()
{
    //nameEditLine->setReadOnly(!nameEditLine->isReadOnly());
    nameEditLine->setReadOnly(false);
    nameEditLine->setFocus();
}

void CardInfoScreen::onEditCard()
{
    emit editCard(nameEditLine->text(),imgSrc);
    cardInfo->setCardName(nameEditLine->text());
    cardInfo->setCardImgSrc(imgSrc);
    if(cardInfo->getIsMagnetLine())
        cardInfo->setMagnet(magnetLineEdit->text());
    else
        cardInfo->setMagnet("");
    emit backPressed(0);
}

void CardInfoScreen::editFlagMagnetLine()
{
    SimpleIcon *icon;
    cardInfo->setFlagMagnetLine(!cardInfo->getIsMagnetLine());
    if(cardInfo->getIsMagnetLine() == true)
    {
        icon = new SimpleIcon(0,":/svg/tools/magnetyes.svg","",infoIconSize);
        if(magnetLineEdit!=NULL)
            magnetLineEdit->show();
    }
    else
    {
        icon = new SimpleIcon(0,":/svg/tools/magnetno.svg","",infoIconSize);
        if(magnetLineEdit!=NULL)
            magnetLineEdit->hide();
    }
    icon->setObjectName("test");
    icon->setAlignment(Qt::AlignCenter);
    //childWidgets.append(icon);
    lineMagnetLayout->replaceWidget(iconMagnet,icon);
    childWidgets.removeOne(iconMagnet);
    delete(iconMagnet);
    iconMagnet = icon;
}

