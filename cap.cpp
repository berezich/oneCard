#include "cap.h"

Cap::~Cap()
{
    for(int i; i<childWidgets.length(); i++)
        delete(childWidgets.at(i));
    for(int i; i<childLayouts.length(); i++)
        delete(childLayouts.at(i));
}

void Cap::setTitle(QString txt, double textSize, int leftMargin, QString color)
{
    titleLbl->setText(txt);
    titleLbl->setFont(QFont("Calibri",textSize));
    titleLbl->setStyleSheet("QLabel { color : "+color+"; }");
    titleLbl->setContentsMargins(leftMargin,0,0,0);
    titleLbl->adjustSize();

}

void Cap::addRightIcon(SimpleIcon *icon, int rightOffset)
{
    hLayout->addWidget(icon);
    hLayout->addSpacing(rightOffset);
    childWidgets.append(icon);
}

void Cap::addLeftIcon(SimpleIcon *icon, int leftOffset)
{
    hLayout->insertWidget(0, icon);
    hLayout->insertSpacing(0,leftOffset);
    childWidgets.append(icon);
}

Cap::Cap(int height, SKIN_COLOR_NAME colorName , QWidget *parent)
{
    this->height = height;
    this->color = InterFace::getSkinColor(colorName).head();

    setMaximumHeight(height);
    setMinimumHeight(height);
    resize(this->width(),height);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(Pal);

    hLayout = new QHBoxLayout();
    hLayout->setMargin(0);
    hLayout->setSpacing(0);

    titleLbl = new QLabel(title);
    titleLbl->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    hLayout->addWidget( titleLbl);
    hLayout->addStretch(1);
    childWidgets.append(titleLbl);

    setLayout(hLayout);
    childLayouts.append( hLayout);
}
