#include "simpleicon.h"

SimpleIcon::SimpleIcon(int id, QString imgScr,  QString imgPushScr, QSize imgSize, QWidget *parent)
{
    this->id = id;
    this->imgScr = imgScr;
    this->imgPushScr = imgPushScr;
    this->imgSize = imgSize;
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
void SimpleIcon::mousePressEvent(QMouseEvent *)
{
    QPixmap pixmap =  picIcon->pixmap(imgSize,QIcon::Selected);
    setPixmap(pixmap);
    setEnabled(!pixmap.isNull());
    adjustSize();
}

void SimpleIcon::mouseReleaseEvent(QMouseEvent *)
{
    QPixmap pixmap=picIcon->pixmap(imgSize,QIcon::Normal);
    setPixmap(pixmap);
    setEnabled(!pixmap.isNull());
    adjustSize();
    emit click(id);
}


