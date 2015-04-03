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
    imgPos = QPoint((-spinSize.width())/2,(-spinSize.height())/2);
    timer.start(15,this);
}

Spinner::~Spinner()
{
    timer.stop();
    while(this->children().length()>0)
        delete(children().last());
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

