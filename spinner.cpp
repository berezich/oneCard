#include "spinner.h"

Spinner::Spinner(double scale, QWidget *parent) : QWidget(parent)
{
    init();
    spanAngle = spanAngle*16;
    screenSize = parent->size();
    setMinimumSize(screenSize);
    setMaximumSize(screenSize);

    penWidth = penWidth*scale;
    spinSize = spinSize*scale;
    //imgPos = QPoint((screenSize.width()-spinSize.width())/2,(screenSize.height()-spinSize.height())/2);
    imgPos = QPoint((-spinSize.width())/2,(-spinSize.height())/2);
    //image = new QImage();
    //image->load(spinImgSrc);
    // Scale the image to given size
    //*image = image->scaled(spinSize, Qt::KeepAspectRatio);
//    pen = new QPen(QColor(spinColor));
//    pen1= new QPen(QColor(spinColor1));
//    pen->setWidth(penWidth);
//    pen1->setWidth(penWidth);
//    rectangle = new QRectF( QRect(imgPos,spinSize) );
    timer.start(15,this);
}

Spinner::~Spinner()
{
    timer.stop();
    while(this->children().length()>0)
        delete(children().last());
    //delete(pen);
    //delete(pen1);
    //delete(rectangle);
}

void Spinner::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(screenSize.width()/2,screenSize.height()/2);
    painter.rotate(angel);
    if(angel>=360)
        angel=0;
    angel+=5;


     int spanAngle1 = 360*16 - spanAngle;

     QPen pen(spinColor);
     QPen pen1(spinColor1);
     pen.setWidth(penWidth);
     pen1.setWidth(penWidth);
     QRectF rectangle( QRect(imgPos,spinSize) );

     painter.setRenderHint(QPainter::Antialiasing );
     painter.setPen(pen);
     painter.drawArc(rectangle, startAngle, spanAngle);
     painter.setPen(pen1);
     painter.drawArc(rectangle,spanAngle,spanAngle1);
     painter.end();
}

void Spinner::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        update();
    } else {
        QWidget::timerEvent(event);
    }
}

