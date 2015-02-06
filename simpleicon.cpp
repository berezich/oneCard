#include "simpleicon.h"

SimpleIcon::SimpleIcon(int id, QString imgScr,  QString imgPushScr, QSize imgSize, bool staySelected, QWidget *parent):QLabel(parent)
{
    this->id = id;
    this->imgScr = imgScr;
    this->imgPushScr = imgPushScr;
    this->imgSize = imgSize;
    this->staySelected = staySelected;
    picIcon = new QIcon(imgScr);
    setPixmap(picIcon->pixmap(imgSize));
    //setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    setMinimumSize(imgSize);
    adjustSize();
}

SimpleIcon::~SimpleIcon()
{
    delete(picIcon);
}

void SimpleIcon::unselectIcon()
{
    QPixmap pixmap=picIcon->pixmap(imgSize,QIcon::Normal);
    setPixmap(pixmap);
    setEnabled(!pixmap.isNull());
    adjustSize();
}

void SimpleIcon::selectIcon()
{
    QPixmap pixmap =  picIcon->pixmap(imgSize,QIcon::Selected);
    setPixmap(pixmap);
    setEnabled(!pixmap.isNull());
    adjustSize();
}

void SimpleIcon::mousePressEvent(QMouseEvent *)
{
    selectIcon();
}

void SimpleIcon::mouseReleaseEvent(QMouseEvent *)
{
    if(!staySelected)
    {
        unselectIcon();
//        QPixmap pixmap=picIcon->pixmap(imgSize,QIcon::Normal);
//        setPixmap(pixmap);
//        setEnabled(!pixmap.isNull());
//        adjustSize();
    }
    emit click(id);
}


