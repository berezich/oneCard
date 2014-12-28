#include "menu.h"

Menu::Menu(QSize size,double scale, QWidget *parent):Overlay(parent)
{

    scaleFactor = scale;
    blankSize = size;

    setMinimumSize(size);
    setMaximumSize(size);

    //rectSize = rectSize*scale;
    menuWidth = menuWidth*scale;
    //rectPoint= QPoint((blankSize.width()-rectSize.width())/2,(blankSize.height()-rectSize.height())/2);
    menuTitleTxtSize =  qSqrt(qSqrt(scale))*menuTitleTxtSize;
    menuItemTxtSize = qSqrt(qSqrt(scale))*menuItemTxtSize;
    setContentsMargins(0,0,blankSize.width()-menuWidth,0);

    menuBasicLayout = new QVBoxLayout();
    menuBasicLayout->setContentsMargins(0,0,0,0);
    setLayout(menuBasicLayout);
    menuWidget = new QWidget();
    menuBasicLayout->addWidget(menuWidget);

    QPalette Pal(menuWidget->palette());
    // set black background
    Pal.setColor(QPalette::Background, backGroundColor);
    menuWidget->setAutoFillBackground(true);
    menuWidget->setPalette(Pal);

    menuLayout = new QVBoxLayout();
    menuWidget->setLayout(menuLayout);

    QLabel *title = new QLabel();
    title->setText(tr("НАСТРОЙКИ"));
    title->setFont(QFont("Calibri",menuTitleTxtSize));
    title->setContentsMargins(10*scaleFactor,10*scaleFactor,0,0);
    title->setStyleSheet("color : "+titleColor+";");
    title->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    menuLayout->addWidget(title);

    menuItemTxt.append(tr("синхронизация устройства"));
    menuItemTxt.append(tr("синхронизация с сервером"));
    menuItemTxt.append(tr("интерфейс"));
    menuItemTxt.append(tr("язык"));
    //синхронизация с сервером","интерфейс","язык"
    QLabel *item = new QLabel();
    for(int i=0; i<menuItemTxt.length(); i++)
    {
        item = new QLabel();
        menuItemLst.append(item);
        item->setText(menuItemTxt[i]);
        item->setFont(QFont("Calibri",menuItemTxtSize));
        item->setContentsMargins(10*scaleFactor,10*scaleFactor,0,0);
        item->setStyleSheet("color : "+lblTxtColor+";");
        item->setAlignment(Qt::AlignLeft|Qt::AlignTop);
        menuLayout->addWidget(item);
    }
    menuLayout->addStretch(1);
}

Menu::~Menu()
{

}

void Menu::mousePressEvent(QMouseEvent *event)
{
    if(event->x() > menuWidth)
        this->hide();

}

