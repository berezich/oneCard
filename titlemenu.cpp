#include "titlemenu.h"

TitleMenu::TitleMenu(int id, QString text, double textSize, int leftOffset, int topOffset, QWidget *parent):QLabel(parent)
{
    this->id = id;
    setContentsMargins(0,0,0,0);
    textLeftOffset = leftOffset;
    textTopOffset = topOffset;
    setText(text);
    setFont(QFont("Calibri",textSize));
    setWordWrap(true);
    setStyleSheet("color : "+txtColor+"; ");
}

TitleMenu::~TitleMenu()
{

}

void TitleMenu::mouseReleaseEvent(QMouseEvent *event)
{
    setStyleSheet("color : "+txtColor+";");
    emit click(id);
}

void TitleMenu::mousePressEvent(QMouseEvent *event)
{
    setStyleSheet("color : "+txtPressColor+";");
}

