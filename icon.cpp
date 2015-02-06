#include "icon.h"

Icon::Icon(QWidget *parent) : QWidget(parent)
{

}

Icon::Icon(int id, QString name, int textSize,  QString imgScr,  QString imgPushScr, QSize imgSize, QSize iconSize, QString textColor, QWidget *parent): QWidget(parent)
{
    this->id = id;
    this->name = name;
    this->imgScr = imgScr;
    this->imgPushScr = imgPushScr;
    this->imgSize = imgSize;
    this->iconSize = iconSize;
    this->textColor = textColor;
    picIcon = new QIcon(imgScr);

    labelIcon = new QLabel();
    labelIcon->setPixmap(picIcon->pixmap(imgSize));
    labelIcon->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    labelIcon->setMinimumSize(imgSize);
    labelIcon->adjustSize();

    vLayout = new QVBoxLayout();
    vLayout->addWidget(labelIcon);

    if(textSize!=-1)
    {
        QLabel *label = new QLabel(this->name);

        label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        label->setFont(QFont("Calibri",textSize));
        label->setStyleSheet("QLabel { color : "+this->textColor+"; }");
        label->adjustSize();

        vLayout->addWidget(label);
    }
    else
    {
        setContentsMargins(0,(iconSize-imgSize).height()*0.15,0,(iconSize-imgSize).height()*0.85);
    }
    vLayout->setSpacing(0);

    setLayout(vLayout);
    setFixedSize(iconSize);
}

Icon::~Icon()
{
    delete(picIcon);
}

    void Icon::mousePressEvent(QMouseEvent *)
    {
        QPixmap pixmap=  picIcon->pixmap(imgSize,QIcon::Selected);
        labelIcon->setPixmap(pixmap);
         labelIcon->setEnabled(!pixmap.isNull());
         labelIcon->adjustSize();
         adjustSize();
    }

    void Icon::mouseReleaseEvent(QMouseEvent *)
    {
        QPixmap pixmap=  picIcon->pixmap(imgSize,QIcon::Normal);
        labelIcon->setPixmap(pixmap);
        labelIcon->setPixmap(pixmap);
        labelIcon->setEnabled(!pixmap.isNull());
        labelIcon->adjustSize();
        adjustSize();
        emit clickIcon(id);
    }

