#include "loadingscreen.h"

LoadingScreen::LoadingScreen(QSize size, double scale, QString msg, QWidget *parent):Overlay(parent)
{
    init();
    this->msg = msg;
    scaleFactor = scale;
    screenSize = size;
    setMinimumSize(size);
    setMaximumSize(size);
    rectSize = rectSize*scale;
    frameCenterOffset = frameCenterOffset*scale;
    rectPoint= QPoint((screenSize.width()-rectSize.width())/2,(screenSize.height()-rectSize.height())/2-frameCenterOffset);
    fontSize = fontSize * qSqrt(qSqrt(scaleFactor));
    txtOffset = txtOffset*scaleFactor;
    txtBottomOffset = txtBottomOffset*scaleFactor;
    QVBoxLayout *scrLayout = new QVBoxLayout();

    //msgFrame = new QWidget();
    //scrLayout->addWidget(msgFrame);
    spin = new Spinner(scale,this);
    scrLayout->addWidget(spin);
    //formBasic->setContentsMargins(rectPoint.x()+10*scaleFactor,rectPoint.y(),rectPoint.x()+10*scaleFactor,rectPoint.y()-12*scaleFactor);
    //timer.start(5,this);

//    font = new QFont("Calibri",fontSize);
//    pen= new QPen(QColor(txtColor));
}

LoadingScreen::~LoadingScreen()
{
    while(this->children().length()>0)
        delete(children().last());
    //delete(pen);
    //delete(font);
}

void LoadingScreen::paintEvent(QPaintEvent *e)
{
    QPainter customPainter(this);
    QFont font ("Calibri",fontSize);
    //QPen pen(QColor(txtColor));
    QPen pen(txtColor);
    customPainter.setRenderHint(QPainter::Antialiasing);
    customPainter.setBrush(QBrush(QColor(backGroundColor)));
    customPainter.drawRoundedRect(QRect(rectPoint,rectSize),xRound,yRound);
    customPainter.setFont(font);
    customPainter.setPen(pen);
    customPainter.drawText(QRect(rectPoint+QPoint(txtOffset,txtOffset),rectSize-QSize(txtOffset*2,txtBottomOffset)), Qt::AlignCenter, msg);
    customPainter.end();
}

//void LoadingScreen::timerEvent(QTimerEvent *event)
//{
//    if (event->timerId() == timer.timerId()) {
//        update();
//    } else {
//        QWidget::timerEvent(event);
//    }

//}


