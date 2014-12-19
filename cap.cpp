#include "cap.h"

Cap::~Cap()
{

}

void Cap::setTitle(QString txt, int textSize, int leftMargin, QString color)
{
    titleLbl->setText(txt);
    titleLbl->setFont(QFont("Calibri",textSize));
    titleLbl->setStyleSheet("QLabel { color : "+color+"; }");
    //titleLbl
    titleLbl->setContentsMargins(leftMargin,0,0,0);
    titleLbl->adjustSize();
    //hLayout->layout()->itemAt(0)->

}

void Cap::addRightIcon(SimpleIcon *icon, int rightOffset)
{
    hLayout->addWidget(icon);
    hLayout->addSpacing(rightOffset);
}


Cap::Cap(int height, QString color , QWidget *parent)
{
    this->height = height;
    this->color = color;

    setMaximumHeight(height);
    setMinimumHeight(height);
    resize(this->width(),height);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(Pal);

    hLayout = new QHBoxLayout();
    hLayout->setMargin(0);

    titleLbl = new QLabel(title);
    titleLbl->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    //titleLbl->setMinimumSize(40,40);
    //titleLbl->resi
    hLayout->addWidget( titleLbl);


//    rightIcon = new QLabel();
//    rightIcon->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
//    hLayout->addWidget(rightIcon);

    setLayout(hLayout);

}


//void Cap::setTitle(QString txt, int leftMargin, int textSize)
//{
//    titleLbl->setText(txt);
//    titleLbl->setFont(QFont("Calibri",textSize));
//    titleLbl->setContentsMargins(leftMargin,0,0,0);
//    return;
//}
