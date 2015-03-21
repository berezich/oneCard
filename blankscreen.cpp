#include "blankscreen.h"

BlankScreen::BlankScreen(QWidget *parent):QWidget(parent)
{

}

BlankScreen::BlankScreen(QScreen *screenInfo, QSize appScrSize, int colorName, QWidget *parent):QWidget(parent)
{
    init();
    this->screenInfo = screenInfo;
    //screenSize = screenInfo->geometry().size();
    screenSize = appScrSize;
    skinColor = colorName;

    scaleFactorW = ((double)screenSize.width())/(double)defaultWidth;
    scaleFactorH = ((double)screenSize.height())/(double)defaultHeight;

    scaleFactor = qMin(scaleFactorW,scaleFactorH);

    //qDebug()<<"scaleW = "<< scaleFactorW <<" scaleH = "<< scaleFactorH;
    //qDebug()<<"scale = "<< scaleFactor;

    capHeight = capHeight*scaleFactor;
    titleLeftMargin =titleLeftMargin*scaleFactor;
    textTitleSize = textTitleSize*qSqrt(qSqrt(scaleFactor));
    capSpacerH = capSpacerH * scaleFactor;
    capRightIconOffset = capRightIconOffset*scaleFactor;

    setMinimumSize(screenSize);
    setMaximumSize(screenSize);

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

