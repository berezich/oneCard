#include "cropimgscreen.h"

CropImgScreen::CropImgScreen(QSize size, double scale, QString imgSrc, QWidget *parent):Overlay(parent)
{
    init();
    scaleFactor = scale;
    screenSize = size;
    setMinimumSize(size);
    setMaximumSize(size);

    sideOff = sideOff*scale;
    iconSize = iconSize*scale;
    frameWidth = frameWidth*scale;
    layout = new QVBoxLayout();
    layout->setSpacing(0);
    setLayout(layout);
    layout->setContentsMargins(0,0,0,0);
    //
    imgIcon = new Cropper(scaleFactor,0,imgSrc,size-QSize(2*sideOff,0),false,this);

    int topOffset = (size.height()-imgIcon->height())/2;
    layout->addSpacing(topOffset);
    layout->addWidget(imgIcon);
    imgIcon->setAlignment(Qt::AlignCenter);
    //imgIcon->setStyleSheet("border: 1px solid red;");
    layout->addStretch(1);
    QWidget *lineWidget = new QWidget(this);
    QHBoxLayout *lineLayout = new QHBoxLayout(lineWidget);
    lineWidget->setLayout(lineLayout);
    lineLayout->setContentsMargins(0,0,0,0);
    lineLayout->addStretch(1);
    iconOk = new SimpleIcon(0,":/svg/tools/OKcamera.svg","",iconSize);
    connect(iconOk,SIGNAL(click(int)),this,SLOT(onIconPressed(int)));
    iconOk->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    lineLayout->addWidget(iconOk);
    iconNo = new SimpleIcon(1,":/svg/tools/NOcamera.svg","",iconSize);
    connect(iconNo,SIGNAL(click(int)),this,SLOT(onIconPressed(int)));
    iconNo->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    lineLayout->addWidget(iconNo);
    lineLayout->addStretch(1);
    layout->addWidget(lineWidget);
    layout->addSpacing(10*scaleFactor);
    lineWidget->adjustSize();
    //cropper = new Cropper(size,sideOff,topOffset,lineWidget->height()+10*scaleFactor,frameWidth,imgIcon);
    //cropper->setStyleSheet("border: 2px solid red;");
}

CropImgScreen::~CropImgScreen()
{
    while(children().length()>0)
        if(children().last())
            delete(children().last());
}

void CropImgScreen::onIconPressed(int i)
{
    if(i==0)//ok
    {
        imgIcon->saveCropImg();
    }
    this->hide();
}

