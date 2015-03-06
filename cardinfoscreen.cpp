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
    /*
    for(int i=0; i<childLayouts.length(); i++)
        if(childLayouts.at(i)!=NULL)
            delete(childLayouts.at(i));
    for(int i=0; i<childWidgets.length(); i++)
        if(childWidgets.at(i)!=NULL)
            delete(childWidgets.at(i));
    */
    while(children().length()>0)
            if(children().last())
                delete(children().last());
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
        connect(icon,SIGNAL(click(int)),this,SLOT(onEditName()));
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


    //frontside of card-------------------
    lineFSide = new QHBoxLayout();

    //для симметричности
    //line->addSpacing(editIconSize.width());

    lineFSide->addStretch(1);

    if(card->getCardImgSrc()!="")
        cardFIcon = new SimpleIcon(0,card->getCardImgSrc(),"",cardIconSize);
    else
        cardFIcon = new SimpleIcon(0,iconsFolder+imgNoPhotoSrc,"",cardIconSize);
    if(dataSrc==LOCAL)
    {
        connect(cardFIcon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        connect(cardFIcon,SIGNAL(click(int)),this,SIGNAL(editFrontSideCropImg()));
    }
    cardFIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    lineFSide->addWidget(cardFIcon);
    childWidgets.append(cardFIcon);
    lineFSide->addStretch(1);
    QWidget *vLineWidget;
    QVBoxLayout *vLine;
    if(dataSrc == LOCAL)
    {

        vLineWidget = new QWidget();
        vLine = new QVBoxLayout();
        vLineWidget->setLayout(vLine);
        vLine->setContentsMargins(0,0,0,0);
        childLayouts.append(vLine);
        childLayouts.append(lineFSide);


        icon = new SimpleIcon(0,iconsFolder+"photo.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editFrontSideCameraImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);
        childWidgets.append(icon);

        icon = new SimpleIcon(0,iconsFolder+"gallery.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editFrontSideGalleryImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);
        lineFSide->addWidget(vLineWidget);
        childWidgets.append(icon);

        vLine->addStretch(1);
        childWidgets.append(vLineWidget);

        lineFSide->addSpacing(rightEditIconOffset);
    }

    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(lineFSide);
    cardInfoListLayout->addWidget(widgetLine);
    childWidgets.append(widgetLine);

    //backside of card-----------------
    lineBSide = new QHBoxLayout();
    //для симметричности
    //line->addSpacing(editIconSize.width());
    lineBSide->addStretch(1);

    //cardIcon = new SimpleIcon(0,card->getCardImgBackSrc(),"",cardIconSize);
    if(card->getCardImgBackSrc()!="")
        cardBIcon = new SimpleIcon(0,card->getCardImgBackSrc(),"",cardIconSize);
    else
        cardBIcon = new SimpleIcon(0,iconsFolder+imgNoPhotoSrc,"",cardIconSize);
    if(dataSrc==LOCAL)
    {
        connect(cardBIcon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        connect(cardBIcon,SIGNAL(click(int)),this,SIGNAL(editBackSideCropImg()));
    }
    cardBIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    lineBSide->addWidget(cardBIcon);
    childWidgets.append(cardBIcon);
    lineBSide->addStretch(1);
    if(dataSrc == LOCAL)
    {
        vLineWidget = new QWidget();
        vLine = new QVBoxLayout();
        vLineWidget->setLayout(vLine);
        vLine->setContentsMargins(0,0,0,0);
        childLayouts.append(vLine);
        childLayouts.append(lineBSide);

        icon = new SimpleIcon(0,iconsFolder+"photo.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideCameraImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);
        childWidgets.append(icon);

        icon = new SimpleIcon(0,iconsFolder+"gallery.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideGalleryImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);
        lineBSide->addWidget(vLineWidget);
        childWidgets.append(icon);

        vLine->addStretch(1);
        childWidgets.append(vLineWidget);

    //    icon = new SimpleIcon(0,":/svg/tools/infophoto.svg",":/svg/tools/infophotoPUSH.svg",editIconSize);
    //    icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
    //    connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideCameraImg()));
    //    line->addWidget(icon);
    //    childWidgets.append(icon);


        lineBSide->addSpacing(rightEditIconOffset);
    }
    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(lineBSide);
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
    if(dataSrc==LOCAL)
        connect(iconMagnet,SIGNAL(click(int)),this,SLOT(clearFocusAll()));

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
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
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

void CardInfoScreen::updateImg(CARD_SIDE cardSide)
{
    SimpleIcon *cardIcon1;
    if(cardSide == FRONTSIDE)
    {
        cardIcon1 = new SimpleIcon(0,cardInfo->getCardImgSrc(),"",cardIconSize);
        lineFSide->replaceWidget(cardFIcon,cardIcon1);
        delete(cardFIcon);
        cardFIcon = cardIcon1;
        connect(cardIcon1,SIGNAL(click(int)),this,SIGNAL(editFrontSideCropImg()));
    }
    else
    {
        cardIcon1 = new SimpleIcon(0,cardInfo->getCardImgBackSrc(),"",cardIconSize);
        lineBSide->replaceWidget(cardBIcon,cardIcon1);
        delete(cardBIcon);
        cardBIcon = cardIcon1;
        connect(cardIcon1,SIGNAL(click(int)),this,SIGNAL(editBackSideCropImg()));
    }
    cardIcon1->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    connect(cardIcon1,SIGNAL(click(int)),this,SLOT(clearFocusAll()));

}

void CardInfoScreen::onEditName()
{
    //nameEditLine->setReadOnly(!nameEditLine->isReadOnly());
    nameEditLine->setReadOnly(false);
    nameEditLine->setFocus();
    QApplication::inputMethod()->show();
}

void CardInfoScreen::onEditCard()
{

    clearFocusAll();
    //emit editCard(nameEditLine->text(),imgSrc);

    /*
    cardInfo->setCardName(nameEditLine->text());
    cardInfo->setCardImgSrc(imgSrc);
    if(cardInfo->getIsMagnetLine())
        if(magnetLineEdit!=NULL)
            cardInfo->setMagnet(magnetLineEdit->text());
        else
            cardInfo->setMagnet("");
    */
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
        {
            magnetLineEdit->show();
            magnetLineEdit->setText("");
        }
    }
    else
    {
        icon = new SimpleIcon(0,":/svg/tools/magnetno.svg","",infoIconSize);
        if(magnetLineEdit!=NULL)
        {
            magnetLineEdit->hide();
            cardInfo->setMagnet("");
        }
    }
    connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
    icon->setAlignment(Qt::AlignCenter);
    //childWidgets.append(icon);
    lineMagnetLayout->replaceWidget(iconMagnet,icon);
    childWidgets.removeOne(iconMagnet);
    delete(iconMagnet);
    iconMagnet = icon;
}

void CardInfoScreen::clearFocusAll()
{
    if(magnetLineEdit!=NULL)
    {
        magnetLineEdit->clearFocus();
        cardInfo->setMagnet(magnetLineEdit->text());
    }
    nameEditLine->clearFocus();
    cardInfo->setCardName(nameEditLine->text());
    QApplication::inputMethod()->hide();
}

void CardInfoScreen::mousePressEvent(QMouseEvent *event)
{
    clearFocusAll();
}

