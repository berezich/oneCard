#include "blankspace.h"

BlankSpace::BlankSpace(QSize availSize,double scale, QWidget *parent) : QWidget(parent)
{
    scaleFactor = scale;
    this->availSize = availSize;
    this->setContentsMargins(0,0,0,0);
    //this->setMinimumSize(availSize);
    this->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Expanding);
}

BlankSpace::~BlankSpace()
{

}


void BlankSpace::showMenu()
{
    menuWidget->showMainMenu();

}

void BlankSpace::initMenu()
{
    menuWidget = new Menu(this->size(),scaleFactor,this);
    menuWidget->hide();
}

