#include "menu.h"

Menu::Menu(QSize size,double scale, QWidget *parent):Overlay(parent)
{

    scaleFactor = scale;
    blankSize = size;

    setMinimumSize(size);
    setMaximumSize(size);

    //rectSize = rectSize*scale;
    menuWidth = menuWidth*scale;
    arrowBackSize = arrowBackSize*scale;
    menuTitleTxtSize =  qSqrt(qSqrt(scale))*menuTitleTxtSize;
    menuItemTxtSize = qSqrt(qSqrt(scale))*menuItemTxtSize;
    iconDevSyncSize = iconDevSyncSize*scale;
    iconBluetoothSize = iconBluetoothSize*scale;
    iconAuthOkSize = iconAuthOkSize*scale;

    setContentsMargins(0,0,blankSize.width()-menuWidth,0);

    menuBasicLayout = new QVBoxLayout();
    menuBasicLayout->setContentsMargins(0,0,0,0);
    setLayout(menuBasicLayout);
    menuWidget = new QWidget();
    menuBasicLayout->addWidget(menuWidget);

    mainMenuItemTxt.append(tr("синхронизация устройства"));
    mainMenuItemTxt.append(tr("синхронизация с сервером"));
    mainMenuItemTxt.append(tr("интерфейс"));
    mainMenuItemTxt.append(tr("язык"));

    languages.append(tr("русский"));

    skins.append(tr("стандартный"));

    //showMainMenu();



}

Menu::~Menu()
{

}

void Menu::mousePressEvent(QMouseEvent *event)
{
    if(event->x() > menuWidth)
    {
        menuExists=false;
        this->hide();
    }

}

void Menu::showMainMenu()
{
    if(menuExists)
    {
        menuExists=false;
        this->hide();
        return;
    }
    menuExists=true;
    QWidget *menuWidget1 = new QWidget();
    menuBasicLayout->replaceWidget(menuWidget,menuWidget1);
    delete(menuWidget);
    menuWidget = menuWidget1;
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
    menuLayout->addSpacing(10*scaleFactor);

    MenuItem *itemB;
    //menuItemBLst.clear();
    for(int i=0; i<mainMenuItemTxt.length(); i++)
    {
        itemB = new MenuItem(i,mainMenuItemTxt[i],menuItemTxtSize,10*scaleFactor, 20*scaleFactor);
        connect(itemB,SIGNAL(click(int)),this,SLOT(showSubMenu(int)));
        //menuItemBLst.append(itemB);
        menuLayout->addWidget(itemB);
    }
    menuLayout->addStretch(1);
    this->show();
}

void Menu::showSubMenu(int mainItem)
{
    QWidget *menuWidget1 = new QWidget();
    menuBasicLayout->replaceWidget(menuWidget,menuWidget1);
    delete(menuWidget);
    menuWidget = menuWidget1;
    QPalette Pal(menuWidget->palette());
    // set black background
    Pal.setColor(QPalette::Background, backGroundColor);
    menuWidget->setAutoFillBackground(true);
    menuWidget->setPalette(Pal);

    menuLayout = new QVBoxLayout();
    menuWidget->setLayout(menuLayout);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    QWidget *titleWidget = new QWidget();
    titleWidget->setLayout(titleLayout);

    SimpleIcon *arrowIcon = new SimpleIcon(-1,":/svg/tools/backArrow.svg","",arrowBackSize);
    arrowIcon->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
    connect(arrowIcon,SIGNAL(click(int)),this,SLOT(showMainMenu()));
    titleLayout->addWidget(arrowIcon);

    TitleMenu *title = new TitleMenu(0,mainMenuItemTxt[mainItem],menuTitleTxtSize,0,0);
    title->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);
    connect(title,SIGNAL(click(int)),this,SLOT(showMainMenu()));

    menuLayout->addWidget(titleWidget);
    menuLayout->addSpacing(10*scaleFactor);

    //mainMenuItemTxt.append(tr("синхронизация устройства"));
    //mainMenuItemTxt.append(tr("синхронизация с сервером"));
//    mainMenuItemTxt.append(tr("интерфейс"));
//    mainMenuItemTxt.append(tr("язык"));

    if(mainItem==0)//синхронизация с устройством
    {
        QWidget *line = new QWidget();
        QHBoxLayout *lineLayout = new QHBoxLayout();
        line->setLayout(lineLayout);
        menuLayout->addWidget(line);

        //226x272
        SimpleIcon *icon = new SimpleIcon(0,":/svg/tools/syncin.svg","",iconBluetoothSize);
        icon->setAlignment(Qt::AlignCenter);
        lineLayout->addWidget(icon);

        icon = new SimpleIcon(0,":/svg/tools/syncout.svg","",iconBluetoothSize);
        icon->setAlignment(Qt::AlignCenter);
        lineLayout->addWidget(icon);

        //123x158
        icon = new SimpleIcon(0,":/svg/tools/bluetooth.svg","",iconDevSyncSize);
        icon->setAlignment(Qt::AlignCenter);
        lineLayout->addWidget(icon);

    }
    else if(mainItem==1)//синхронизция с сервером
    {
        QLabel *lbl = new QLabel(tr("логин"));
        menuLayout->addWidget(lbl);
        lbl->setContentsMargins(0,0,0,0);
        lbl->setFont(QFont("Calibri",menuItemTxtSize));
        lbl->setStyleSheet("color : "+titleColor+";");
        lbl->setAlignment(Qt::AlignLeft|Qt::AlignTop);


        login = new QLineEdit();
        menuLayout->addWidget(login);
        login->setFont(QFont("Calibri",menuItemTxtSize));
        login->setStyleSheet("color : "+lblTxtColor+";");

        lbl = new QLabel(tr("пароль"));
        menuLayout->addWidget(lbl);
        lbl->setContentsMargins(0,0,0,0);
        lbl->setFont(QFont("Calibri",menuItemTxtSize));
        lbl->setStyleSheet("color : "+titleColor+";");
        lbl->setAlignment(Qt::AlignLeft|Qt::AlignTop);

        pass = new QLineEdit();
        menuLayout->addWidget(pass);
        pass->setFont(QFont("Calibri",menuItemTxtSize));
        pass->setStyleSheet("color : "+lblTxtColor+";");
        pass->setEchoMode(QLineEdit::Password);

        menuLayout->addSpacing(20*scaleFactor);
        SimpleIcon *iconOk = new SimpleIcon(-2,":/svg/tools/loginok.svg","",iconAuthOkSize);
        iconOk->setAlignment(Qt::AlignCenter);

        menuLayout->addWidget(iconOk);
    }
    if(mainItem==2)//интерфейс
    {

        MenuItem *itemB;
        //menuItemBLst.clear();

        for(int i=0; i<skins.length(); i++)
        {
            itemB = new MenuItem(i,skins[i],menuItemTxtSize,10*scaleFactor+arrowBackSize.width(), 20*scaleFactor);
            //menuItemBLst.append(itemB);
            menuLayout->addWidget(itemB);
        }
    }
    else if(mainItem==3)//язык
    {

        MenuItem *itemB;
        //menuItemBLst.clear();

        for(int i=0; i<languages.length(); i++)
        {
            itemB = new MenuItem(i,languages[i],menuItemTxtSize,10*scaleFactor+arrowBackSize.width(), 20*scaleFactor);
            //menuItemBLst.append(itemB);
            menuLayout->addWidget(itemB);
        }
    }
    menuLayout->addStretch(1);
}

