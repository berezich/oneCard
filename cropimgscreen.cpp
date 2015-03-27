#include "cropimgscreen.h"

CropImgScreen::CropImgScreen(QSize size, double scale, QString imgSrc, QString fileNameForSave, QWidget *parent):Overlay(parent)
{
    init();
    this->fileNameForSave = fileNameForSave;
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

    imgIcon = new Cropper(scaleFactor,0,imgSrc,size-QSize(2*sideOff,0),false,this);

    int topOffset = (size.height()-imgIcon->height())/2;
    layout->addSpacing(topOffset);
    layout->addWidget(imgIcon);
    imgIcon->setAlignment(Qt::AlignCenter);
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
}

CropImgScreen::~CropImgScreen()
{
    while(children().length()>0)
        if(children().last())
            delete(children().last());
}

void CropImgScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Back)
    {
        hide();
        return;
    }
}

void CropImgScreen::onIconPressed(int i)
{
    if(i==0)//ok
    {
        imgIcon->saveCropImg(fileNameForSave);
        emit imgCropped(fileNameForSave);
    }
    this->hide();
}

