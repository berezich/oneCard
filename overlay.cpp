#include <QPainter>
#include <QPen>
#include "overlay.h"

Overlay::Overlay(QWidget *parent) : QWidget(parent)
{

    setPalette(Qt::transparent);

    QSize size = ((QWidget*)this->parent())->size();
    this->setMinimumHeight(size.height());
    this->setMinimumWidth(size.width());
    QColor backgroundColor = "#191a1b" /*palette().light().color()*/;

    backgroundColor.setAlpha(200);

    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, backgroundColor);
    setAutoFillBackground(true);
    setPalette(Pal);

    //setAttribute(Qt::WA_TransparentForMouseEvents);
}

Overlay::~Overlay()
{

}

void Overlay::paintEvent(QPaintEvent *event)
{
//    QSize size = ((QWidget*)parent())->size();
//    this->setMinimumHeight(size.height());
//    this->setMinimumWidth(size.width());
//    QColor backgroundColor = "#191a1b" /*palette().light().color()*/;

//    backgroundColor.setAlpha(200);

//    QPalette Pal(palette());
//    // set black background
//    Pal.setColor(QPalette::Background, backgroundColor);
//    setAutoFillBackground(true);
//    setPalette(Pal);

    //QPainter customPainter(this);
    //customPainter.fillRect(rect(),backgroundColor);

//    QPainter painter(this);

//    painter.setRenderHint(QPainter::Antialiasing);

//    painter.setPen(QPen(Qt::red));

//    painter.drawLine(width()/8, height()/8, 7*width()/8, 7*height()/8);

//    painter.drawLine(width()/8, 7*height()/8, 7*width()/8, height()/8);

}







