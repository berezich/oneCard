#include "galeryscreen.h"

GalleryScreen::GalleryScreen(QScreen *screenInfo, QSize appScrSize, int colorName, QString fotoDir, QWidget *parent):BlankScreen(screenInfo,appScrSize, colorName,parent)
{
    init();
    iconSize = iconSize*scaleFactor;
    cameraDir = fotoDir;
    //cap
    cap = new Cap(capHeight, skinColor);
    cap->setTitle(title,textTitleSize,titleLeftMargin);
    blankLayout->addWidget(cap);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(pressBack()));
    cap->addLeftIcon(icon,capLeftIconOffset);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);
    setLayout(blankLayout);

    gridLayout = new QGridLayout(this);
    blankSpace->setLayout(gridLayout);
    gridLayout->setSpacing(5*scaleFactor);
    blankLayout->addStretch();

}

void GalleryScreen::showCameraPhotos()
{
    setPhotoLst(cameraDir);
}
GalleryScreen::~GalleryScreen()
{
    clearScreen();
}

void GalleryScreen::clearScreen()
{
    photoLst.clear();
    while(children().length()>0)
        if(children().last())
            delete(children().last());
}

void GalleryScreen::setPhotoLst(QString path)
{
    ImgIcon *photoIcon;
    QWidget *widget;
    QDir cameraDir = QDir( path );
    cameraDir.setSorting(QDir::Time);
    QStringList filters;
    filters << "*.jpg";
    cameraDir.setNameFilters(filters);
    photoLst = cameraDir.entryList();


    QString filePath="";
    if(photoLst.length()>0)
        filePath = cameraDir.absoluteFilePath(photoLst.at(0));

    for(int i=0; i<columnsNum*rowsNum; i++)
    {
        if(i < photoLst.length())
        {
            photoIcon = new ImgIcon(i,cameraDir.absoluteFilePath(photoLst.at(i)),iconSize);
            photoIcon->setAlignment(Qt::AlignCenter);
            connect(photoIcon,SIGNAL(click(int)),this,SLOT(onClickPhotoIcon(int)));
            gridLayout->addWidget(photoIcon, qFloor(i/columnsNum),i%columnsNum);
        }
        else
        {
            widget = new QWidget();
        }
    }
}

void GalleryScreen::onClickPhotoIcon(int iPhoto)
{
    QString name = photoLst.at(iPhoto);
    emit selectPic(cameraDir,name);
}
