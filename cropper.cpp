#include "cropper.h"

Cropper::Cropper(double scale, int id, QString imgScr, QSize imgSize, bool isExpand, QWidget *parent) : ImgIcon(id,imgScr,imgSize, isExpand, parent)
{
    curPos = QPoint(0,0);
    startPos=QPoint(-1,-1);
    this->scaleFactor = scale;
    this->frameWidth = frameWidth*scaleFactor;
    this->imageSrc = imgScr;
    this->imgSize = getQImg()->size();
    this->sideOff = ((parent->size()-imgSize)/2).width();
}

Cropper::~Cropper()
{

}

void Cropper::saveCropImg(QString file)
{
    if(startPos!=QPoint(-1,-1)&&curPos!=startPos)
    {
        qDebug()<<"OrigQImg size = "<<getOrigQImg()->size();
        qDebug()<<"QImg size = "<<imgSize;
        double k = ((double) getOrigQImg()->size().width())/((double)imgSize.width());
        qDebug()<<"koef = "<<k;
        //QImage cropped = getQImg()->copy(startPos.x(),startPos.y(),curPos.x()-startPos.x(),curPos.y()-startPos.y());
        QImage cropped = getOrigQImg()->copy(startPos.x()*k,startPos.y()*k,(curPos.x()-startPos.x())*k,(curPos.y()-startPos.y())*k);
        bool res = cropped.save(file);
        qDebug()<<"cropped save res = "<<res;
    }
    else
    {
        if(!QFile::exists(file))
        {
            getQImg()->save(file);
            qDebug()<<"cropped save res = seve the same size";
        }
        else
            qDebug()<<"cropped save res = undefined size of img";
    }
}

bool Cropper::event(QEvent *e)
{
    switch (e->type()) {

    case QEvent::MouseButtonPress:
    {
        curPos  =  ((QMouseEvent*)e)->pos();

        curPos -= QPoint(sideOff,0);
        if(curPos.x() >= 0 && curPos.y()>=0)
            startPos = curPos;
        else
            startPos = QPoint(-1,-1);
        qDebug() <<"Press: " << curPos;
        update();

        return true;
    }
    case QEvent::MouseMove:
    {
        QPoint curPos1  =  ((QMouseEvent*)e)->pos();
        curPos1 -= QPoint(sideOff,0);
        if(startPos.x() >= 0 && startPos.y()>=0)
            if(curPos1.x()>=0 && curPos1.x() < imgSize.width())
            {
                curPos.setX(curPos1.x());
                update();
            }
            if(curPos1.y()>0 && curPos1.y() < imgSize.height())
            {
                curPos.setY(curPos1.y());
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
    if(startPos!=QPoint(-1,-1)&&curPos.x() >= 0 && curPos.y()>=0 && curPos!=startPos)
    {
        QPainter customPainter(this);

        QPen pen(Qt::red);
        pen.setWidth(frameWidth);
        QRectF rectangle( QRectF(startPos+QPoint(sideOff,0),curPos+QPoint(sideOff,0)) );
        customPainter.setPen(pen);
        customPainter.drawRect(rectangle);
    }

}
