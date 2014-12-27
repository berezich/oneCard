#include "imgicon.h"

ImgIcon::ImgIcon(int id, QString imgScr,  QSize imgSize, QWidget *parent)
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

    //pixmap = pixmap.fromImage(picImg->scaled(imgSize,Qt::KeepAspectRatio));
    pixmap = pixmap.fromImage(picImg->scaled(imgSize,Qt::KeepAspectRatioByExpanding));

    delete(picImg);
    picIcon = new QIcon(pixmap);
    setPixmap(pixmap);

    setMinimumSize(imgSize);
    adjustSize();
}

ImgIcon::~ImgIcon()
{
    delete(picIcon);
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
