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

    //cap
    cap = new Cap(capHeight, skinColor);
    cap->setTitle(title,textTitleSize,titleLeftMargin);
    blankLayout->addWidget(cap);
    blankLayout->addSpacing(capSpacerH);
    //-------

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

    cardInfoListLayout = new QVBoxLayout();
    cardInfoListLayout->setSpacing(spacingSize);
    cardInfoListLayout->setContentsMargins(0,0,0,0);
    blankSpace->setLayout(cardInfoListLayout);

}

CardInfoScreen::~CardInfoScreen()
{
    while(children().length()>0)
            if(children().last())
                delete(children().last());
    magnetLineEdit=NULL;
}

void CardInfoScreen::showCardInfo(CardInfo *card, DATA_SOURCE dataSrc)
{
    QHBoxLayout *line;
    QWidget *widgetLine;
    imgSrc = card->getCardImgSrc();
    cardInfo = card;

    cardInfoListLayout->setSpacing(spacingSize);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SLOT(onEditCard()));
    cap->addLeftIcon(icon,capLeftIconOffset);

    //cardName-------------------------
    line = new QHBoxLayout();

    nameEditLine = new QLineEdit(card->getCardName());
    nameEditLine->setObjectName("cardName");
    nameEditLine->setFont(QFont("Calibri",textCardNameSize));
    nameEditLine->setAlignment(Qt::AlignHCenter| Qt::AlignTop);
    nameEditLine->setReadOnly(true);
    nameEditLine->setMaxLength(14);
    nameEditLine->setStyleSheet("border: 0px; background: "+backGroundColor+";");

    line->addWidget(nameEditLine);
    if(dataSrc == LOCAL)
    {
        icon = new SimpleIcon(0,iconsFolder+"pen.svg","",editIconSize);
        connect(icon,SIGNAL(click(int)),this,SLOT(onEditName()));
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        line->addWidget(icon);
        line->addSpacing(rightEditIconOffset);
    }

    widgetLine = new QWidget();
    widgetLine->setLayout(line);
    widgetLine->setMinimumWidth(screenSize.width());
    cardInfoListLayout->addWidget(widgetLine);

    //frontside of card-------------------
    lineFSide = new QHBoxLayout();
    lineFSide->addStretch(1);

    if(card->getCardImgSrc()!="")
        cardFIcon = new ImgIcon(0,card->getCardImgSrc(),cardIconSize,false);
    else
        cardFIcon = new ImgIcon(0,iconsFolder+imgNoPhotoSrc,cardIconSize,false);
    if(dataSrc==LOCAL)
    {
        connect(cardFIcon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        connect(cardFIcon,SIGNAL(click(int)),this,SIGNAL(editFrontSideCropImg()));
    }
    cardFIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    lineFSide->addWidget(cardFIcon);
    lineFSide->addStretch(1);
    QWidget *vLineWidget;
    QVBoxLayout *vLine;
    if(dataSrc == LOCAL)
    {

        vLineWidget = new QWidget();
        vLine = new QVBoxLayout();
        vLineWidget->setLayout(vLine);
        vLine->setContentsMargins(0,0,0,0);

        icon = new SimpleIcon(0,iconsFolder+"photo.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editFrontSideCameraImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);

        icon = new SimpleIcon(0,iconsFolder+"gallery.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editFrontSideGalleryImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);
        lineFSide->addWidget(vLineWidget);
        vLine->addStretch(1);

        lineFSide->addSpacing(rightEditIconOffset);
    }

    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(lineFSide);
    cardInfoListLayout->addWidget(widgetLine);

    //backside of card-----------------
    lineBSide = new QHBoxLayout();
    lineBSide->addStretch(1);

    if(card->getCardImgBackSrc()!="")
        cardBIcon = new ImgIcon(0,card->getCardImgBackSrc(),cardIconSize,false);
    else
        cardBIcon = new ImgIcon(0,iconsFolder+imgNoPhotoSrc,cardIconSize,false);
    if(dataSrc==LOCAL)
    {
        connect(cardBIcon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        connect(cardBIcon,SIGNAL(click(int)),this,SIGNAL(editBackSideCropImg()));
    }
    cardBIcon->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
    lineBSide->addWidget(cardBIcon);
    lineBSide->addStretch(1);
    if(dataSrc == LOCAL)
    {
        vLineWidget = new QWidget();
        vLine = new QVBoxLayout();
        vLineWidget->setLayout(vLine);
        vLine->setContentsMargins(0,0,0,0);

        icon = new SimpleIcon(0,iconsFolder+"photo.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideCameraImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);

        icon = new SimpleIcon(0,iconsFolder+"gallery.svg","",editIconSize);
        icon->setAlignment(Qt::AlignTop | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SIGNAL(editBackSideGalleryImg()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        vLine->addWidget(icon);
        lineBSide->addWidget(vLineWidget);

        vLine->addStretch(1);
        lineBSide->addSpacing(rightEditIconOffset);
    }
    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(lineBSide);
    cardInfoListLayout->addWidget(widgetLine);

    //magnet line-----------------------------
    lineMagnetLayout = new QHBoxLayout();
    lineMagnetLayout->addStretch(1);

    if(card->getIsMagnetLine())
        iconMagnet = new SimpleIcon(0,":/svg/tools/magnetyes.svg","",infoIconSize);
    else
        iconMagnet = new SimpleIcon(0,":/svg/tools/magnetno.svg","",infoIconSize);
    if(dataSrc==LOCAL)
        connect(iconMagnet,SIGNAL(click(int)),this,SLOT(clearFocusAll()));

    iconMagnet->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
    lineMagnetLayout->addWidget(iconMagnet);

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
    }

    lineMagnetLayout->addStretch(1);

    if(dataSrc == LOCAL)
    {
        icon = new SimpleIcon(0,iconsFolder+"pen.svg","",editIconSize);
        icon->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        connect(icon,SIGNAL(click(int)),this,SLOT(editFlagMagnetLine()));
        connect(icon,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
        lineMagnetLayout->addWidget(icon);
        lineMagnetLayout->addSpacing(rightEditIconOffset);
    }

    widgetLine = new QWidget();
    widgetLine->setMinimumWidth(screenSize.width());
    widgetLine->setLayout(lineMagnetLayout);

    cardInfoListLayout->addWidget(widgetLine);
    cardInfoListLayout->addStretch(1);

}

void CardInfoScreen::updateImg(CARD_SIDE cardSide)
{
    ImgIcon *cardIcon1;
    if(cardSide == FRONTSIDE)
    {
        cardIcon1 = new ImgIcon(0,cardInfo->getCardImgSrc(),cardIconSize,false);
        lineFSide->replaceWidget(cardFIcon,cardIcon1);
        delete(cardFIcon);
        cardFIcon = cardIcon1;
        connect(cardIcon1,SIGNAL(click(int)),this,SIGNAL(editFrontSideCropImg()));
        cardIcon1->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
        connect(cardIcon1,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
    }
    else
    {
        cardIcon1 = new ImgIcon(0,cardInfo->getCardImgBackSrc(),cardIconSize,false);
        lineBSide->replaceWidget(cardBIcon,cardIcon1);
        delete(cardBIcon);
        cardBIcon = cardIcon1;
        connect(cardIcon1,SIGNAL(click(int)),this,SIGNAL(editBackSideCropImg()));
        cardIcon1->setAlignment(Qt::AlignHCenter| Qt::AlignTop );
        connect(cardIcon1,SIGNAL(click(int)),this,SLOT(clearFocusAll()));
    }


}

void CardInfoScreen::onEditName()
{
    nameEditLine->setReadOnly(false);
    nameEditLine->setFocus();
    QApplication::inputMethod()->show();
}

void CardInfoScreen::onEditCard()
{

    clearFocusAll();
    emit backPressed();
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
    lineMagnetLayout->replaceWidget(iconMagnet,icon);
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

void CardInfoScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Back)
    {
        emit backPressed(true);
        return;
    }
}
