#include "galeryscreen.h"

GalleryScreen::GalleryScreen(QScreen *screenInfo,QSize appScrSize,QString fotoDir, QWidget *parent):BlankScreen(screenInfo,appScrSize,parent)
{
    //iconHeight = iconHeight*scaleFactor;
    //iconWidth = iconWidth*scaleFactor;

    cameraDir = fotoDir;
    //шапка
    cap = new Cap(capHeight);
    childWidgets.append(cap);
    cap->setTitle(title,textTitleSize,titleLeftMargin);


    blankLayout->addWidget(cap);
    childLayouts.append(blankLayout);

    SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/backArrow.svg",":/svg/tools/backArrowPUSH.svg",QSize(55,55)*scaleFactor);
    icon->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
    connect(icon,SIGNAL(click(int)),this,SIGNAL(pressBack()));
    cap->addLeftIcon(icon,capLeftIconOffset);


    //blankLayout->addSpacing(capSpacerH);

    blankSpace = new QWidget();
    blankLayout->addWidget(blankSpace);

    setLayout(blankLayout);

    iconSize = iconSize*scaleFactor;
    //textSize = textSize*qSqrt(qSqrt(scaleFactor));

    gridLayout = new QGridLayout(this);
    blankSpace->setLayout(gridLayout);
    childLayouts.append(gridLayout);
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
    for(int i=0; i<childLayouts.length(); i++)
        if(childLayouts.at(i)!=NULL)
            delete(childLayouts.at(i));
    for(int i=0; i<childWidgets.length(); i++)
        if(childWidgets.at(i)!=NULL)
            delete(childWidgets.at(i));
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
            childWidgets.append(photoIcon);
        }
        else
        {
            widget = new QWidget();
            childWidgets.append(widget);
            gridLayout->addWidget(widget, qFloor(i/columnsNum),i%columnsNum);
        }

    }
    childWidgets.append(blankSpace);
}

void GalleryScreen::onClickPhotoIcon(int iPhoto)
{
    QString name = photoLst.at(iPhoto);
    emit selectPic(cameraDir,name);
}
