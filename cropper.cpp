#include "cropper.h"

Cropper::Cropper(double scale, int id, QString imgScr, QSize imgSize, bool isExpand, QWidget *parent) : ImgIcon(id,imgScr,imgSize, isExpand, parent)
{
    curPos = QPoint(0,0);
    startPos=QPoint(0,0);
    this->scaleFactor = scale;
    this->frameWidth = frameWidth*scaleFactor;
    this->imageSrc = imgScr;
    /*
    this->screenSize = imgSize;

    this->sideOff = sideOff;
    this->bottomOff = bottomOff;
    this->topOffset = isExpand;
    setMinimumSize(((QWidget*)parent)->height(),imgSize.width());
    setMaximumSize(((QWidget*)parent)->height(),imgSize.width());
    */
    //setContentsMargins(sideOff,0,sideOff,0);
}

Cropper::~Cropper()
{

}

void Cropper::saveCropImg()
{
    QImage cropped = getQImg()->copy(startPos.x(),startPos.y(),curPos.x(),curPos.y());
    cropped.save("C:\\Users\\Sashka\\AppData\\Roaming\\oneCard\\crop_");
}

bool Cropper::event(QEvent *e)
{
    switch (e->type()) {

    case QEvent::MouseButtonPress:
    {
        curPos  =  ((QMouseEvent*)e)->pos();
        startPos = curPos;
        qDebug() <<"Press: " << curPos;
        update();

        return true;
    }
    case QEvent::MouseMove:
    {
        QPoint curPos1  =  ((QMouseEvent*)e)->pos();
        qDebug() <<"Move: " << curPos;
        //if(curPos1.x()>=sideOff && curPos1.x() < screenSize.width()-sideOff)
            //if(curPos1.y()>0 && curPos1.y() < ((QWidget*)parent())->height())
            //{
        if(curPos1.x()>=0 && curPos1.x() < ((QWidget*)parent())->width()-2)
            if(curPos1.y()>0 && curPos1.y() < ((QWidget*)parent())->height()-6)
                {
                    qDebug()<<"parent height = " <<((QWidget*)parent())->height();
                    curPos = curPos1;
                    update();
                }


        return true;
    }
    default:
        return ImgIcon::event(e);
    }
    return true;

}

void Cropper::paintEvent(QPaintEvent *e)
{
    ImgIcon::paintEvent(e);
    if(curPos!=startPos)
    {
        QPainter customPainter(this);

        QPen pen(Qt::red);
        pen.setWidth(frameWidth);
        /*
        if(curPos.y()>screenSize.height()-bottomOff)
            curPos.setY(screenSize.height()-bottomOff);
        if(curPos.y()<2)
            curPos.setY(2);
        if(curPos.x()>screenSize.width()-sideOff)
            curPos.setX(screenSize.width()-sideOff);
        if(curPos.x()<sideOff)
            curPos.setX(sideOff);
            */
        QRectF rectangle( QRectF(startPos,curPos) );
        customPainter.setPen(pen);
        customPainter.drawRect(rectangle);
    }

}
