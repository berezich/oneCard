#include "blankscreen.h"

BlankScreen::BlankScreen(QScreen *screenInfo, QWidget *parent):QWidget(parent)
//BlankScreen::BlankScreen(QScreen *screenInfo)
{
//    this->screenInfo = screenInfo;
//    screenSize = screenInfo->geometry().size();
//    scaleFactor = screenSize.width()/defaultWidth;
//    capHeight = capHeight*scaleFactor;
//    qDebug()<<"scale = "<< scaleFactor;
//    setMinimumSize(screenSize);

    this->screenInfo = screenInfo;
    screenSize = screenInfo->geometry().size();
    scaleFactor = screenSize.width()/defaultWidth;

    qDebug()<<"scale = "<< scaleFactor;


    capHeight = capHeight*scaleFactor;
    titleLeftMargin =titleLeftMargin*scaleFactor;
    textTitleSize = textTitleSize*qSqrt(scaleFactor);
    capSpacerH = capSpacerH * scaleFactor;
    capRightIconOffset = capRightIconOffset*scaleFactor;

    setMinimumSize(screenSize);

    blankLayout = new QBoxLayout(QBoxLayout::TopToBottom,this);


    blankLayout->setSpacing(0);
    blankLayout->setMargin(0);

    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, backGroundColor);
    setAutoFillBackground(true);
    setPalette(Pal);

}

BlankScreen::~BlankScreen()
{

}

