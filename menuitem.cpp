#include "menuitem.h"


MenuItem::MenuItem(int id, QString text, double textSize, int leftOffset, int topOffset, QWidget *parent):QPushButton(parent)
{
    init();
    this->id = id;
    textLeftOffset = leftOffset;
    textTopOffset = topOffset;
    this->textSize = textSize;
    setText(text);

    setFont(QFont("Calibri",textSize));
    //setContentsMargins(leftOffset,0,0,0);
    setPalette(Qt::transparent);
    setFocusPolicy(Qt::NoFocus);

    setStyleSheet("color : "+txtColor+"; padding-bottom: "+QString::number( textTopOffset/2)+"px; padding-top: "+QString::number( textTopOffset/2)+"px;  padding-left: "+QString::number(leftOffset)+"px; text-align: left; border-width: 0px; border-style: solid;" );
}

MenuItem::~MenuItem()
{

}

void MenuItem::setUnerLine(bool val)
{
    QFont font = QFont("Calibri",textSize);
    font.setUnderline(val);
    setFont(font);
}

void MenuItem::mouseReleaseEvent(QMouseEvent *event)
{
    setStyleSheet("color : "+txtColor+"; padding-bottom: "+QString::number( textTopOffset/2)+"px; padding-top: "+QString::number( textTopOffset/2)+"px; text-align: left; padding-left: "+QString::number(textLeftOffset)+"px; border-width: 0px; border-style: solid;");
    //setStyleSheet("color : "+txtColor+";");
    emit click(id);
}

void MenuItem::mousePressEvent(QMouseEvent *event)
{
    setStyleSheet("color : "+txtPressColor+";padding-bottom: "+QString::number( textTopOffset/2)+"px;  padding-top: "+QString::number( textTopOffset/2)+"px; text-align: left; padding-left: "+QString::number(textLeftOffset)+"px; border-width: 0px; border-style: solid;" );
    //setStyleSheet("color : "+txtPressColor+";");
}

