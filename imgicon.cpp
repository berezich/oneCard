#include "imgicon.h"

ImgIcon::ImgIcon(int id, QString imgScr,  QSize imgSize, bool isExpand, QWidget *parent):QLabel(parent)
{
    this->id = id;
    this->imgScr = imgScr;
    this->imgSize = imgSize;


    picImg = new QImage(imgScr);
    if(picImg->height()>picImg->width())
    {
        QTransform trans;
        picImgRotate = new QImage( picImg->transformed(trans.rotate(-90)));
        delete(picImg);
        picImg = picImgRotate;
    }

    if(isExpand)
    {
        *picImg = picImg->scaled(imgSize,Qt::KeepAspectRatioByExpanding);
        pixmap = pixmap.fromImage(*picImg);
    }
    else
    {
        *picImg = picImg->scaled(imgSize,Qt::KeepAspectRatio);
        pixmap = pixmap.fromImage(*picImg);
        //pixmap = pixmap.fromImage(picImg->scaled(imgSize,Qt::KeepAspectRatio));
    }
    //delete(picImg);
    picIcon = new QIcon(pixmap);
    setPixmap(pixmap);

    if(isExpand)
        setMinimumSize(imgSize);
    adjustSize();
}

ImgIcon::~ImgIcon()
{
    delete(picIcon);
    delete(picImg);
}
void ImgIcon::mousePressEvent(QMouseEvent *)
{
    QPixmap pixmap =  picIcon->pixmap(imgSize,QIcon::Selected);
    setPixmap(pixmap);
    setEnabled(!pixmap.isNull());
    adjustSize();
}

void ImgIcon::mouseReleaseEvent(QMouseEvent *)
{
    QPixmap pixmap=picIcon->pixmap(imgSize,QIcon::Normal);
    setPixmap(pixmap);
    setEnabled(!pixmap.isNull());
    adjustSize();
    emit click(id);
}
