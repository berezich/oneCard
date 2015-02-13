#include "menu.h"

Menu::Menu(QSize size, double scale, Settings *settings, QWidget *parent):Overlay(parent)
{
    init();
    scaleFactor = scale;
    blankSize = size;
    backGroundColor = InterFace::getSkinColor(settings->skinColor()).options();
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
    this->settings = settings;
    menuBasicLayout = new QVBoxLayout();
    menuBasicLayout->setContentsMargins(0,0,0,0);
    setLayout(menuBasicLayout);
    menuWidget = new QWidget();
    menuBasicLayout->addWidget(menuWidget);

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

void Menu::showMainMenu(bool showInAnyway)
{
    if(!showInAnyway)
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
    curSubMenu = mainItem;
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
    connect(arrowIcon,SIGNAL(click(int)),this,SLOT(backToMainMenu()));
    titleLayout->addWidget(arrowIcon);

    TitleMenu *title = new TitleMenu(0,mainMenuItemTxt[mainItem],menuTitleTxtSize,0,0);
    title->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);
    connect(title,SIGNAL(click(int)),this,SLOT(backToMainMenu()));

    menuLayout->addWidget(titleWidget);
    menuLayout->addSpacing(10*scaleFactor);


    if(mainItem==0)//синхронизация с устройством
    {
        QWidget *line = new QWidget();
        QHBoxLayout *lineLayout = new QHBoxLayout();
        line->setLayout(lineLayout);
        menuLayout->addWidget(line);

        //226x272
        SimpleIcon *icon = new SimpleIcon(0, InterFace::getSkinColor(settings->skinColor()).iconFolder()+"syncin.svg","",iconBluetoothSize);
        icon->setAlignment(Qt::AlignCenter);
        lineLayout->addWidget(icon);

        icon = new SimpleIcon(0,InterFace::getSkinColor(settings->skinColor()).iconFolder()+"syncout.svg","",iconBluetoothSize);
        icon->setAlignment(Qt::AlignCenter);
        lineLayout->addWidget(icon);

        //123x158
        icon = new SimpleIcon(0,":/svg/tools/bluetooth.svg","",iconDevSyncSize);
        icon->setAlignment(Qt::AlignCenter);
        lineLayout->addWidget(icon);

    }
    else if(mainItem==1)//синхронизция с сервером
    {
        menuLayout->addSpacing(10*scaleFactor);
        QLabel *lbl = new QLabel(tr("сервер"),this);
        menuLayout->addWidget(lbl);
        lbl->setContentsMargins(0,0,0,0);
        lbl->setFont(QFont("Calibri",menuItemTxtSize));
        lbl->setStyleSheet("color : "+titleColor+";");
        lbl->setAlignment(Qt::AlignLeft|Qt::AlignTop);

        endPoint = new QLineEdit();
        menuLayout->addWidget(endPoint);
        endPoint->setFont(QFont("Calibri",menuItemTxtSize));
        endPoint->setStyleSheet("color : "+lblTxtColor+";");
        endPoint->setText(settings->endPoint());

        menuLayout->addSpacing(10*scaleFactor);
        lbl = new QLabel(tr("логин"),this);
        menuLayout->addWidget(lbl);
        lbl->setContentsMargins(0,0,0,0);
        lbl->setFont(QFont("Calibri",menuItemTxtSize));
        lbl->setStyleSheet("color : "+titleColor+";");
        lbl->setAlignment(Qt::AlignLeft|Qt::AlignTop);

        login = new QLineEdit();
        menuLayout->addWidget(login);
        login->setFont(QFont("Calibri",menuItemTxtSize));
        login->setStyleSheet("color : "+lblTxtColor+";");
        login->setText(settings->login());

        menuLayout->addSpacing(10*scaleFactor);
        lbl = new QLabel(tr("пароль"),this);
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
        pass->setText(settings->pass());

        menuLayout->addSpacing(20*scaleFactor);
        SimpleIcon *iconOk = new SimpleIcon(-2,":/svg/tools/loginok.svg","",iconAuthOkSize);
        iconOk->setAlignment(Qt::AlignCenter);
        connect(iconOk,SIGNAL(click(int)),this,SLOT(onChangeServer()));

        menuLayout->addWidget(iconOk);
    }
    if(mainItem==2)//интерфейс
    {

        MenuItem *itemB;
        colorOptions.clear();
        for(int i=0; i<skins.length(); i++)
        {
            itemB = new MenuItem(i,skins[i],menuItemTxtSize,10*scaleFactor+arrowBackSize.width(), 20*scaleFactor);
            colorOptions.append(itemB);
            if(i==settings->skinColor())
                itemB->setUnerLine(true);
            connect(itemB,SIGNAL(click(int)),this,SLOT(onChangeColor(int)));
            menuLayout->addWidget(itemB);
        }

        menuLayout->addSpacing(30*scaleFactor);
        QLabel *lblGrpView = new QLabel(grpViewLblText,this);
        lblGrpView->setContentsMargins(0,0,0,0);
        lblGrpView->setStyleSheet("QLabel{color:"+titleColor+"; text-align: left; padding-left:"+QString::number(arrowBackSize.width())+"px;}");
        lblGrpView->setFont(QFont("Calibri",menuTitleTxtSize));
        menuLayout->addWidget(lblGrpView);
        grpViewOptions.clear();
        for(int i=0; i<grpViews.length(); i++)
        {
            itemB = new MenuItem(i,grpViews[i],menuItemTxtSize,10*scaleFactor+arrowBackSize.width(), 20*scaleFactor);
            grpViewOptions.append(itemB);
            if(i==settings->grpView())
                itemB->setUnerLine(true);
            connect(itemB,SIGNAL(click(int)),this,SLOT(onChangeGrpView(int)));
            menuLayout->addWidget(itemB);
        }
    }
    else if(mainItem==3)//язык
    {

        MenuItem *itemB;
        //menuItemBLst.clear();
        languageOptions.clear();
        for(int i=0; i<languages.length(); i++)
        {
            itemB = new MenuItem(i,languages[i],menuItemTxtSize,10*scaleFactor+arrowBackSize.width(), 20*scaleFactor);
            languageOptions.append(itemB);
            if(i==settings->lang())
                itemB->setUnerLine(true);
            connect(itemB,SIGNAL(click(int)),this,SLOT(onChangeLanguage(int)));
            //menuItemBLst.append(itemB);
            menuLayout->addWidget(itemB);
        }
    }
    else if(mainItem==4)//вход в каталог
    {

        MenuItem *itemB,*itemB1;
        //menuItemBLst.clear();
        defEnterOptions.clear();

        itemB = new MenuItem(1,tr("включить"),menuItemTxtSize,10*scaleFactor+arrowBackSize.width(), 20*scaleFactor);
        itemB1 = new MenuItem(0,tr("выключить"),menuItemTxtSize,10*scaleFactor+arrowBackSize.width(), 20*scaleFactor);
        defEnterOptions.append(itemB1);
        defEnterOptions.append(itemB);
        if(settings->defEnterApp())
            itemB->setUnerLine(true);
        else
            itemB1->setUnerLine(true);

        connect(itemB,SIGNAL(click(int)),this,SLOT(onChangeDefEnter(int)));
        connect(itemB1,SIGNAL(click(int)),this,SLOT(onChangeDefEnter(int)));
        //menuItemBLst.append(itemB);
        menuLayout->addWidget(itemB);
        menuLayout->addWidget(itemB1);
    }
    menuLayout->addStretch(1);
}

void Menu::backToMainMenu()
{
    showMainMenu(true);
}

void Menu::onChangeColor(int color)
{
    ((MenuItem*)colorOptions[color])->setUnerLine(true);
    ((MenuItem*)colorOptions[settings->skinColor()])->setUnerLine(false);
    settings->setSkinColor(color);
    backGroundColor = InterFace::getSkinColor(settings->skinColor()).options();
    QPalette Pal(menuWidget->palette());
    // set black background
    Pal.setColor(QPalette::Background, backGroundColor);
    menuWidget->setAutoFillBackground(true);
    menuWidget->setPalette(Pal);
    menuWidget->show();
    emit changeSettings(COLOR);
}

void Menu::onChangeServer()
{
    settings->setLogin(login->text());
    settings->setPass(pass->text());
    settings->setEndPoint(endPoint->text());
    qDebug()<<"login = "<<settings->login()<<"pass = "<<settings->pass()<<"endPoint = "<<settings->endPoint();
}

void Menu::onChangeLanguage(int lang)
{
    ((MenuItem*)languageOptions[lang])->setUnerLine(true);
    ((MenuItem*)languageOptions[settings->lang()])->setUnerLine(false);
    settings->setLang(lang);


    if(myappTranslator!=NULL)
    {
        delete(myappTranslator);
    }
    myappTranslator = new QTranslator();
    QString tsFile = Languages::getLangTs(settings->lang());
    myappTranslator->load(tsFile);
    QApplication::instance()->installTranslator(myappTranslator);
    qDebug()<<"set ts file = "+tsFile;
    translateNames();
    showSubMenu(curSubMenu);
    //emit changeSettings(LANGUAGE);
}

void Menu::onChangeGrpView(int grpView)
{
    ((MenuItem*)grpViewOptions[grpView])->setUnerLine(true);
    ((MenuItem*)grpViewOptions[settings->grpView()])->setUnerLine(false);
    settings->setGrpView(grpView);
    emit changeSettings(GRP_VIEW);
}

void Menu::onChangeDefEnter(int isEnter)
{
    settings->setDefEnterApp(isEnter==1);
    if(isEnter==1)
    {
        ((MenuItem*)defEnterOptions[1])->setUnerLine(true);
        ((MenuItem*)defEnterOptions[0])->setUnerLine(false);
    }
    else
    {
        ((MenuItem*)defEnterOptions[1])->setUnerLine(false);
        ((MenuItem*)defEnterOptions[0])->setUnerLine(true);
    }
}

