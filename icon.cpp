#include "icon.h"

Icon::Icon(QWidget *parent) : QWidget(parent)
{

}

Icon::Icon(int id, QString name, int textSize,  QString imgScr,  QString imgPushScr, QSize imgSize, QSize iconSize, QWidget *parent)
{
    this->id = id;
    this->name = name;
    this->imgScr = imgScr;
    this->imgPushScr = imgPushScr;
    this->imgSize = imgSize;
    picIcon = new QIcon(imgScr);

    labelIcon = new QLabel();
    labelIcon->setPixmap(picIcon->pixmap(imgSize));
    //labelIcon->setPixmap(picIcon->pixmap(imgSize));
    labelIcon->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    //labelIcon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    labelIcon->setMinimumSize(imgSize);
    labelIcon->adjustSize();

    //labelIcon->setStyleSheet("border: 1px solid red");
    QLabel *label = new QLabel(this->name);

    label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    label->setFont(QFont("Calibri",textSize));
    //label->setStyleSheet("border: 1px solid red");
    label->adjustSize();
    vLayout = new QVBoxLayout();

    vLayout->addWidget(labelIcon);
    if(textSize!=-1)
        vLayout->addWidget(label);
    vLayout->setSpacing(0);

    setLayout(vLayout);
    adjustSize();

    //setMinimumSize(width(),height());
    //labelIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //connect(this,SINGAL(mousePressEvent(QMouseEvent *)),this,SLOT(pushIcon(QMouseEvent *)));

    //resize(iconSize);
}

Icon::~Icon()
{

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

