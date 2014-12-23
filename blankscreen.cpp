#include "blankscreen.h"

BlankScreen::BlankScreen(QScreen *screenInfo, QWidget *parent):QWidget(parent)
{

    this->screenInfo = screenInfo;
    screenSize = screenInfo->geometry().size();
    scaleFactor = ((double)screenSize.width())/(double)defaultWidth;
    scaleFactorH = ((double)screenSize.height())/(double)defaultHeight;

    qDebug()<<"scaleW = "<< scaleFactor <<"scaleH = "<< scaleFactorH;


    //capHeight = capHeight*scaleFactor;
    capHeight = capHeight*scaleFactorH;
    titleLeftMargin =titleLeftMargin*scaleFactor;
    //textTitleSize = textTitleSize*qSqrt(scaleFactor);
    textTitleSize = textTitleSize*qSqrt(scaleFactorH);
    //capSpacerH = capSpacerH * scaleFactor;
    capSpacerH = capSpacerH * scaleFactorH;
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

