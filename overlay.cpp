#include <QPainter>
#include <QPen>
#include "overlay.h"

Overlay::Overlay(QWidget *parent) : QWidget(parent)
{

    setPalette(Qt::transparent);

    QSize size = ((QWidget*)this->parent())->size();
    this->setMinimumHeight(size.height());
    this->setMinimumWidth(size.width());
    QColor backgroundColor = "#191a1b";

    backgroundColor.setAlpha(200);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, backgroundColor);
    setAutoFillBackground(true);
    setPalette(Pal);

}

Overlay::~Overlay()
{

}





