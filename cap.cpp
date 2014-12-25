#include "cap.h"

Cap::~Cap()
{

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
}

void Cap::addLeftIcon(SimpleIcon *icon, int leftOffset)
{
    hLayout->insertWidget(0, icon);
    hLayout->insertSpacing(0,leftOffset);
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
    hLayout->setSpacing(0);

    titleLbl = new QLabel(title);
    titleLbl->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    hLayout->addWidget( titleLbl);
    hLayout->addStretch(1);

    setLayout(hLayout);

}
